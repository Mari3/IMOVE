#include <boost/interprocess/managed_shared_memory.hpp>
#include <thread>

#include "ImoveSceneManager.hpp"

#include "OpenCVUtil.hpp"
#include "../../scene_interface/src/Person.h"
#include "../../scene_interface/src/Vector2.h"
#include "Scene/LightTrail/LightTrailScene.h"
#include "Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "Windows/SceneWindow.hpp"

//#include <scene_interface_sma/SharedMemory.hpp>
//#include <scene_interface_sma/Person.hpp>
//#include <scene_interface_sma/Vector2.hpp>
#include "../../scene_interface_sma/src/SharedMemory.hpp"
#include "../../scene_interface_sma/src/Person.hpp"
#include "../../scene_interface_sma/src/Vector2.hpp"

void ImoveSceneManager::sendSceneFrameThread(ImoveSceneManager* imove_scene_manager, sf::Image sf_image) {
	imove_scene_manager->sendSceneFrame(sf_image);
}

ImoveSceneManager::ImoveSceneManager(Calibration* calibration, LightTrailConfiguration& configuration_lighttrail) {
	this->calibration = calibration;

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
	// Get the extracted people queue in the segment
	this->extractedpeople_queue = this->segment->find<scene_interface_sma::ExtractedpeopleQueue>(scene_interface_sma::NAME_EXTRACTEDPEOPLE_QUEUE).first;
	// Get the people extractor scene frames queue in the segment
	this->pi_sceneframe_queue = this->segment->find<peopleextractor_interface_sma::SceneframeQueue>(peopleextractor_interface_sma::NAME_SCENEFRAME_QUEUE).first;
	// Get the whole running class
	this->running = this->segment->find<Running>(NAME_SHARED_MEMORY_RUNNING).first;
}

void ImoveSceneManager::run() {
	// setup scene window
	SceneWindow window_scene(this->calibration->getResolutionProjector(), this->calibration->getFullscreenProjector());

	// setup clock
	sf::Clock clock;

	std::thread* previous_thread = NULL;

	float dt;
	float capture_dt = 0;
	float SPF_capture_scene = 1.f / (float) this->calibration->getFpsCaptureScene();
	
	// while q not pressed
	while (window_scene.shouldKeepOpen() && this->running->running) {
		this->receiveExtractedpeopleAndUpdateScene();
		
		// draw next Scene frame based on clock difference
		dt = clock.restart().asSeconds();
		this->scene->update(dt);
		
		// draw the actual Scene on window
		window_scene.drawScene(this->scene);
		
		capture_dt += dt;
		if (capture_dt > SPF_capture_scene) {
			if (previous_thread != NULL) {
				previous_thread->join();
			}
			previous_thread = new std::thread(ImoveSceneManager::sendSceneFrameThread, this, window_scene.captureFrameScene());
			capture_dt -= SPF_capture_scene;
		}
	}
}

void ImoveSceneManager::receiveExtractedpeopleAndUpdateScene() {
	if (!this->extractedpeople_queue->empty()) {
		//create vector of extracted people for input of scene
		std::vector<scene_interface::Person> extractedpeople;
		
		// receive extracted people from shared memory from peopleextractor
		boost::interprocess::offset_ptr<scene_interface_sma::PersonVector> extractedpeople_ptr = this->extractedpeople_queue->pop();
		
		extractedpeople = std::vector<scene_interface::Person>();
		for (unsigned int i = 0; i < extractedpeople_ptr->size(); ++i) {
			// receive extracted person from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Person> si_person = extractedpeople_ptr->at(i);
			
			// create person type from shared memory person type
			scene_interface::PersonType person_type;
			switch (si_person->getPersonType()) {
				case scene_interface_sma::PersonType::Bystander:
					person_type = scene_interface::PersonType::Bystander;
					break;
				case scene_interface_sma::PersonType::Passerthrough:
					person_type = scene_interface::PersonType::Passerthrough;
					break;
				case scene_interface_sma::PersonType::Participant:
					person_type = scene_interface::PersonType::Participant;
					break;
				case scene_interface_sma::PersonType::StandingStill:
					person_type = scene_interface::PersonType::StandingStill;
					break;
				case scene_interface_sma::PersonType::None:
					person_type = scene_interface::PersonType::None;
					break;
			}
			// receive locations from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Vector2Vector> locations = si_person->getLocations();
			// receive location from shared memory
			boost::interprocess::offset_ptr<scene_interface_sma::Vector2> location = locations->front();

			// create extracted person for input of scene from received extracted person from shared memory and add extracted person to vector of extracted people
			extractedpeople.push_back(
				scene_interface::Person(
					si_person->getId(),
					scene_interface::Vector2(
						location->getX(),
						location->getY()
					),
					person_type
				)
			);
		}
		
		// update scene with extracted people from peopleextractor
		this->scene->updatePeople(extractedpeople);
	}
}

void ImoveSceneManager::sendSceneFrame(const sf::Image& frame_scene) {
	// create shared memory scene frame from sfml image
	sf::Vector2u size_image = frame_scene.getSize();
	boost::interprocess::offset_ptr<peopleextractor_interface_sma::Image> pi_sceneframe = this->segment->construct<peopleextractor_interface_sma::Image>(boost::interprocess::anonymous_instance)(
		((unsigned int) size_image.x) / this->calibration->getFactorResizeCaptureScene(), 
		((unsigned int) size_image.y) / this->calibration->getFactorResizeCaptureScene(),
		this->segment
	);
	for (unsigned int x = 0; x < ((unsigned int) size_image.x) / this->calibration->getFactorResizeCaptureScene(); ++x) {
		for (unsigned int y = 0; y < ((unsigned int) size_image.y) / this->calibration->getFactorResizeCaptureScene(); ++y) {
			sf::Color sf_pixel = frame_scene.getPixel(
				x * (signed int) this->calibration->getFactorResizeCaptureScene(),
				y * (signed int) this->calibration->getFactorResizeCaptureScene()
			);
			pi_sceneframe->setRGB(x, y, (unsigned char) sf_pixel.r, (unsigned char) sf_pixel.g, (unsigned char) sf_pixel.b);
		}
	}

	// push on shared memory queue for people extractor to pop
	this->pi_sceneframe_queue->push_back(pi_sceneframe);
}
