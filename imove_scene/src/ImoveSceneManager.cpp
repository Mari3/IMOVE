#include <boost/interprocess/managed_shared_memory.hpp>
#include <thread>

#include "ImoveSceneManager.hpp"

#include "../../scene_interface/src/People.h"
#include "Scene/LightTrail/LightTrailScene.h"
#include "Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "Windows/SceneWindow.hpp"

#include "../../scene_interface_sma/src/SharedMemory.hpp"

void ImoveSceneManager::sendingSceneFrameThread(ImoveSceneManager* imove_scene_manager) {
	imove_scene_manager->sendingSceneFrame();
}

ImoveSceneManager::ImoveSceneManager(Calibration& calibration, const LightTrailSceneConfiguration& configuration_lighttrail) :
calibration(calibration),
projection(Projection(calibration))
{
	// setup scene
  this->scene = new LightTrailScene(
		configuration_lighttrail,
    new LightSourceVectorRepository(),
    new LightTrailVectorRepository(),
    new GravityPointVectorRepository(),
    new ColorHoleVectorRepository(),
    new LightPersonMapRepository()
  );
	// Shared memory segment
  this->segment = new boost::interprocess::managed_shared_memory(boost::interprocess::open_only, scene_interface_sma::NAME_SHARED_MEMORY);
	// Construct the people extracted queue in shared memory
	this->si_people_queue = this->segment->find<scene_interface_sma::PeopleQueue>(scene_interface_sma::NAME_PEOPLE_QUEUE).first;
	this->pi_sceneframe_queue = this->segment->find<peopleextractor_interface_sma::SceneframeQueue>(peopleextractor_interface_sma::NAME_SCENEFRAME_QUEUE).first;
	// Get the whole running class
	this->running = this->segment->find<Running>(NAME_SHARED_MEMORY_RUNNING).first;
}

void ImoveSceneManager::run() {
	// setup scene window
	SceneWindow window_scene(this->calibration.getResolutionProjector(), this->calibration.getFullscreenProjector());

	// setup clock
	sf::Clock clock;

	float dt;
	float capture_dt = 0;
	float SPF_capture_scene = 1.f / (float) this->calibration.getFpsCaptureScene();
	
	// while allowed to run
	while (this->running->running) {
		this->receiveExtractedpeopleAndUpdateScene();
		
		// draw next Scene frame based on clock difference
		dt = clock.restart().asSeconds();
		this->scene->update(dt);
		
		// draw the actual Scene on window
		window_scene.drawScene(this->scene);
		
		capture_dt += dt;
		if (capture_dt > SPF_capture_scene) {
			capture_dt -= SPF_capture_scene;
		}
		
		// if window should be closed, shutdown application
		if (!window_scene.shouldKeepOpen()) {
			this->running->running = false;
			this->running->reboot_on_shutdown = false;
		}
	}
}

void ImoveSceneManager::receiveExtractedpeopleAndUpdateScene() {
	if (!this->si_people_queue->empty()) {
		//create vector of extracted people for input of scene
		scene_interface::People extractedpeople;
		
		// receive extracted people from shared memory from peopleextractor
		boost::interprocess::offset_ptr<scene_interface_sma::People> si_people = this->si_people_queue->front();
		
		extractedpeople = scene_interface::People();
		for (unsigned int i = 0; i < si_people->size(); ++i) {
			// receive extracted person from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Person> si_person = si_people->at(i);
			
			// create person type from shared memory person type
			scene_interface::Person::PersonType person_type;
			switch (si_person->getPersonType()) {
				case scene_interface_sma::Person::PersonType::Bystander:
					person_type = scene_interface::Person::PersonType::Bystander;
					break;
				case scene_interface_sma::Person::PersonType::Passerthrough:
					person_type = scene_interface::Person::PersonType::Passerthrough;
					break;
				case scene_interface_sma::Person::PersonType::Participant:
					person_type = scene_interface::Person::PersonType::Participant;
					break;
				case scene_interface_sma::Person::PersonType::None:
					person_type = scene_interface::Person::PersonType::None;
					break;
			}
			// create person type from shared memory person type
			scene_interface::Person::MovementType movement_type;
			switch (si_person->getMovementType()) {
				case scene_interface_sma::Person::MovementType::StandingStill:
					movement_type = scene_interface::Person::MovementType::StandingStill;
					break;
				case scene_interface_sma::Person::MovementType::Moving:
					movement_type = scene_interface::Person::MovementType::Moving;
					break;
			}
			// receive locations from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Locations> locations = si_person->getLocations();
			// receive location from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Location> location = locations->front();

			// create extracted person for input of scene from received extracted person from shared memory and add extracted person to vector of extracted people
			extractedpeople.push_back(
				scene_interface::Person(
					si_person->getId(),
					scene_interface::Location(
						location->getX(),
						location->getY()
					),
					person_type,
					movement_type
				)
			);
		}
		
		// update scene with extracted people from peopleextractor
		this->scene->updatePeople(extractedpeople);

		// Remove last extracted people from queue
		this->si_people_queue->pop_front();
	}
}

void ImoveSceneManager::sendingSceneFrame() {
	boost::interprocess::offset_ptr<peopleextractor_interface_sma::SceneframeQueue>& pi_sceneframe_queue = this->pi_sceneframe_queue;
	boost::interprocess::offset_ptr<Running>& running = this->running;
	const Calibration& calibration = this->calibration;
	std::queue<sf::Image>& sceneframe_queue = this->sceneframe_queue;
	boost::interprocess::managed_shared_memory* segment = this->segment;

	while (running->running) {
		if (!sceneframe_queue.empty()) {
			const sf::Image frame_scene = sceneframe_queue.front();
			// create shared memory scene frame from sfml image
			sf::Vector2u size_image = frame_scene.getSize();
			boost::interprocess::offset_ptr<peopleextractor_interface_sma::Image> pi_sceneframe = segment->construct<peopleextractor_interface_sma::Image>(boost::interprocess::anonymous_instance)(
				((unsigned int) size_image.x) / calibration.getFactorResizeCaptureScene(),
				((unsigned int) size_image.y) / calibration.getFactorResizeCaptureScene(),
				segment
			);
			for (unsigned int x = 0; x < ((unsigned int) size_image.x) / calibration.getFactorResizeCaptureScene(); ++x) {
				for (unsigned int y = 0; y < ((unsigned int) size_image.y) / calibration.getFactorResizeCaptureScene(); ++y) {
					sf::Color sf_pixel = frame_scene.getPixel(
						x * (signed int) calibration.getFactorResizeCaptureScene(),
						y * (signed int) calibration.getFactorResizeCaptureScene()
					);
					pi_sceneframe->setRGB(x, y, (unsigned char) sf_pixel.r, (unsigned char) sf_pixel.g, (unsigned char) sf_pixel.b);
				}
			}

			// push on shared memory queue for people extractor to pop
			pi_sceneframe_queue->push_back(pi_sceneframe);
			sceneframe_queue.pop();
		}
	}
}
