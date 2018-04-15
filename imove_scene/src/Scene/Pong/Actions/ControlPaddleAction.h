#ifndef IMOVE_CONTROLPADDLEACTION_H
#define IMOVE_CONTROLPADDLEACTION_H

#include "../../Action.h"
#include "../PongScene.h"
#include "../PongConfiguration.h"

class ControlPaddleAction : public Action {
private:
	std::shared_ptr<Paddle> paddle;
	std::shared_ptr<PongPerson> person;
	bool isLeft;
	PongConfiguration config;
public:
	ControlPaddleAction(std::shared_ptr<Paddle> paddle, std::shared_ptr<PongPerson> person, bool isLeft, PongConfiguration config);
	bool isDone(std::vector<Action*> &followUp);
	void execute(float dt);
};

#endif //IMOVE_CONTROLPADDLEACTION_H
