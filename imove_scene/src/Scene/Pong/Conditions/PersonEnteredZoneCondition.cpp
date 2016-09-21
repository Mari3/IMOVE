#include "PersonEnteredZoneCondition.h"

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
	if(!p1->isControlled){ //If paddle 1 is not already controlled
		people->for_each([&](std::shared_ptr<PongPerson> person){
			if(person->person_type == scene_interface::Person::Participant
				&& person->location.x > 0 && person->location.x < config.controlRange){
				actions.push_back(static_cast<Action*>(new ControlPaddleAction(p1,person,true,config)));
			}
		});
	}

	if(!p2->isControlled){
		people->for_each([&](std::shared_ptr<PongPerson> person){
			if(person->person_type == scene_interface::Person::Participant
				&& person->location.x > config.screenWidth-config.controlRange && person->location.x < config.screenWidth){
				actions.push_back(static_cast<Action*>(new ControlPaddleAction(p2,person,false,config)));
			}
		});
	}

	return actions.size();
}