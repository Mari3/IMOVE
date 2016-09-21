#include "ControlPaddleAction.h"

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
	if(isLeft){
		if(person->location.x > config.controlRange*3)
			res = true;
	}else if(person->location.x < config.screenWidth-config.controlRange*3){
		res = true;
	}

	if(!res && person->person_type != scene_interface::Person::Participant){
		res = true;
	}

	if(res){
		paddle->isControlled = false;
		return true;
	}
	return false;
}

void ControlPaddleAction::execute(float dt) {
	paddle->y = person->location.y;
}