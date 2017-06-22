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
	float newY = person->location.y;
	float prev_target = paddle->y_target;
	// if (std::abs(newY - paddle->y) > 200) {
	// 	if (newY > 0 && newY < config.screenHeight) {
	// 			paddle->y_target = newY - 80;
	// 			paddle->y = newY - 80;
	// 	}
	// } else
	if (std::abs(newY - paddle->y_target - 80) > 40.0) {
		//std::cout << "Diff = " << std::abs(newY - paddle->y_target) << " > 40" << std::endl;
		if (newY > 0 && newY < config.screenHeight) {
				//std::cout << "prev: " << paddle->prev_target << std::endl;
				paddle->prev_target = prev_target;
				paddle->y_target = newY - 80;
				//std::cout << "curr: " << paddle->y_target << std::endl;
		}
	}
	if (paddle->prev_target - paddle->y_target > 0) {
		//std::cout << "prev y: " << paddle->y << std::endl;
		if (paddle->y >= paddle->y_target) {
			paddle->y -= 20;
		}
		//std::cout << "new y: " << paddle->y << std::endl;
	} else if (paddle->prev_target - paddle->y_target < 0) {
		//std::cout << "prev y: " << paddle->y << std::endl;
		if (paddle->y <= paddle->y_target) {
			paddle->y += 20;
		}
		//std::cout << "new y: " << paddle->y << std::endl;
	}

	// if (paddle->y <= paddle->y_target + 25) {
	// 	paddle->y+=20;
	// } else if (paddle->y >= paddle->y_target - 25) {
	// 	paddle->y-=20;
	// }
}
