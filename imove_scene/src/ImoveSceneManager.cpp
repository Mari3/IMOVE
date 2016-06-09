#include <boost/interprocess/managed_shared_memory.hpp>

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

const unsigned int SIZE_SHAREDMEMORY = 100000000; // 100MB

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
	
	// Newly create a new shared memory segment with certain size
	boost::interprocess::shared_memory_object::remove(scene_interface_sma::NAME_SHARED_MEMORY);
	segment = new boost::interprocess::managed_shared_memory(boost::interprocess::create_only, scene_interface_sma::NAME_SHARED_MEMORY, SIZE_SHAREDMEMORY);
	// Construct the people extracted queue in shared memory
	this->extractedpeople_queue = segment->construct<scene_interface_sma::ExtractedpeopleQueue>(scene_interface_sma::NAME_EXTRACTEDPEOPLE_QUEUE)(128);
}

void ImoveSceneManager::run() {
	// setup scene window
	SceneWindow window_scene(this->calibration->getResolutionProjector());

	// setup clock
	sf::Clock clock;
	
	float dt;
	while (true) {
		this->receiveExtractedpeopleAndUpdateScene();
		
		// draw next Scene frame based on clock difference
		dt = clock.restart().asSeconds();
		//dt = 1.f/24.f;
		this->scene->update(dt);
		
		// draw the actual Scene on window
		window_scene.drawScene(this->scene);
	}

	//destroy shared memory segment
	boost::interprocess::shared_memory_object::remove(scene_interface_sma::NAME_SHARED_MEMORY);
	this->segment = NULL;
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
				case scene_interface_sma::PersonType::None:
					person_type = scene_interface::PersonType::None;
					break;
			}
			// create person type from shared memory person type
			scene_interface::MovementType movement_type;
			switch (si_person->getMovementType()) {
				case scene_interface_sma::MovementType::StandingStill:
					movement_type = scene_interface::MovementType::StandingStill;
					break;
				case scene_interface_sma::MovementType::Moving:
					movement_type = scene_interface::MovementType::Moving;
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
					person_type,
					movement_type
				)
			);
		}
		
		// update scene with extracted people from peopleextractor
		this->scene->updatePeople(extractedpeople);
	}
}
