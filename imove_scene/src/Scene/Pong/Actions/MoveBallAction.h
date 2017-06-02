#ifndef IMOVE_PONG_MOVEBALLACTION_H
#define IMOVE_PONG_MOVEBALLACTION_H

#include "../../Action.h"
#include "../PongScene.h"
#include "../PongConfiguration.h"

class MoveBallAction : public Action {
private:
	std::shared_ptr<Ball> ball;
	PongConfiguration config;
public:
	MoveBallAction(std::shared_ptr<Ball> ball, PongConfiguration config);
	bool isDone(std::vector<Action*> &followUp);
	void execute(float dt);
};

#endif //IMOVE_PONG_MOVEBALLACTION_H
