#include "ControlPaddleAction.h"
#include <iostream>

ControlPaddleAction::ControlPaddleAction(
	std::shared_ptr<Paddle> paddle, std::shared_ptr<PongPerson> person, bool isLeft, PongConfiguration config) :
	paddle(paddle),
	person(person),
	isLeft(isLeft),
	config(config)
{
	paddle->isControlled = true;
}

bool ControlPaddleAction::isDone(std::vector<Action*> &followUp){
	bool res = false;

	if(!res && person->person_type != scene_interface::Person::Player){
		res = true;
	}

	if(res){
		paddle->isControlled = false;
		// std::cout << "isDone action = true"  << std::endl;
		return true;
	}
	// std::cout << "isDone action = false"  << std::endl;
	return false;
}

void ControlPaddleAction::execute(float dt) {
	paddle->y = person->location.y;
}
