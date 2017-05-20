#include "PersonEnteredZoneCondition.h"
#include <iostream>

PersonEnteredZoneCondition::PersonEnteredZoneCondition(
	Repository<PongPerson>* people,
	std::shared_ptr<Paddle> p1,
	std::shared_ptr<Paddle> p2,
	PongConfiguration config
) : people(people),
	p1(p1),
	p2(p2),
	config(config)
{}

int PersonEnteredZoneCondition::check(float dt, std::vector<Action *> &actions){
	// std::cout << "people size" + std::to_string(people->size()) << std::endl;
	if(!p1->isControlled){ //If paddle 1 is not already controlled
		people->for_each([&](std::shared_ptr<PongPerson> person){
			// std::cout << "x location = " + std::to_string(person->location.x) << std::endl;
			// std::cout << "person type = " + std::to_string(person->person_type) << std::endl;
			if(person->person_type == scene_interface::Person::Player
			/* && person->location.x > 0*/ && person->location.x < 960 /*config.controlRange*/){
				// std::cout << "in orange zone" << std::endl;
				actions.push_back(static_cast<Action*>(new ControlPaddleAction(p1,person,true,config)));
			}
		});
	}

	if(!p2->isControlled){
		people->for_each([&](std::shared_ptr<PongPerson> person){
			// std::cout << "x location = " + std::to_string(person->location.x) << std::endl;
			// std::cout << "person type = " + std::to_string(person->person_type) << std::endl;
			if(person->person_type == scene_interface::Person::Player
				&& person->location.x > 960/*config.screenWidth-300 && person->location.x < config.screenWidth*/){
				// std::cout << "in blue zone" << std::endl;
				actions.push_back(static_cast<Action*>(new ControlPaddleAction(p2,person,false,config)));
			}
		});
	}

	return actions.size();
}
