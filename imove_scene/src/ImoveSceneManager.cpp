#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/offset_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp> 
#include <boost/interprocess/offset_ptr.hpp>
#include <string>
#include <iostream>
#include <cstdlib> //std::system

#include "ImoveSceneManager.hpp"

#include "OpenCVUtil.hpp"
#include "Interface/Person.h"
#include "Scene/LightTrail/LightTrailScene.h"
#include "Scene/LightTrail/Repositories/LightsSceneVectorRepositories.h"
#include "Windows/SceneWindow.hpp"

//#include <scene_interface/ExtractedpeopleQueue.hpp>
//#include <scene_interface/Person.hpp>
//#include <scene_interface/Vector2.hpp>
#include "../../scene_interface/src/ExtractedpeopleQueue.hpp"
#include "../../scene_interface/src/Person.hpp"
#include "../../scene_interface/src/Vector2.hpp"

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
}

void ImoveSceneManager::run() {
	// delete (left over) on construction and delete on destruction
	struct shm_remove {
		shm_remove() { boost::interprocess::shared_memory_object::remove("ImoveSharedMemory"); }
		~shm_remove(){ boost::interprocess::shared_memory_object::remove("ImoveSharedMemory"); }
	} remover;
	
	//Create a new segment with given name and size
	boost::interprocess::managed_shared_memory segment(boost::interprocess::create_only, "ImoveSharedMemory", 100000000); // 65536

	//Construct a queue named "root" in shared memory
	boost::interprocess::offset_ptr<scene_interface::ExtractedpeopleQueue> extractedpeople_queue = segment.construct<scene_interface::ExtractedpeopleQueue>("root")(128);
	
	// setup scene window
	SceneWindow window_scene(this->calibration->getResolutionProjector());

	// setup clock
	sf::Clock clock;
	
	std::vector<Person> detected_people;
	float dt;
	// while no key pressed
	while (true) {
		if (!extractedpeople_queue->empty()) {
			boost::interprocess::offset_ptr<scene_interface::PersonVector> detected_people_ptr = extractedpeople_queue->pop();
			detected_people = std::vector<Person>();
			for (unsigned int i = 0; i < detected_people_ptr->size(); ++i) {
				boost::interprocess::offset_ptr<scene_interface::Person> si_person = detected_people_ptr->at(i);
			//for (boost::interprocess::offset_ptr<scene_interface::Person> si_person : detected_people_ptr) {
				PersonType person_type;
				switch (si_person->getPersonType()) {
					case scene_interface::PersonType::Bystander:
						person_type = PersonType::Bystander;
						break;
					case scene_interface::PersonType::Passerthrough:
						person_type = PersonType::Passerthrough;
						break;
					case scene_interface::PersonType::Participant:
						person_type = PersonType::Participant;
						break;
					case scene_interface::PersonType::None:
						person_type = PersonType::None;
						break;
				}
				boost::interprocess::offset_ptr<scene_interface::Vector2Vector> locations = si_person->getLocations();
				boost::interprocess::offset_ptr<scene_interface::Vector2> location = locations->front();
				float x = location->getX();
				float y = location->getY();
				Vector2 vector2(
					x,
					y
				);
				Person person = Person(
					vector2,
					person_type	
				);
				detected_people.push_back(person);
			}
		}
		//todo destruct

		// update scene with location of people
		this->scene->updatePeople(detected_people);

		// draw next Scene frame based on clock difference
		dt = clock.restart().asSeconds();
		//dt = 1.f/24.f;
		this->scene->update(dt);
		
		// draw the actual Scene on window
		window_scene.drawScene(this->scene);
	}
}
