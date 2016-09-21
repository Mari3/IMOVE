#ifndef IMOVE_PONG_RESTARTBALLACTION_H
#define IMOVE_PONG_RESTARTBALLACTION_H

#include "../../Action.h"
#include "../PongScene.h"
#include "../../Util/Timer.h"

class RestartBallAction : public Action {
private:
	std::shared_ptr<Ball> ball;
	bool left, done = false;
	Timer timer;
	PongConfiguration config;
public:
	RestartBallAction(std::shared_ptr<Ball> ball, bool left, PongConfiguration config);
	bool isDone(std::vector<Action*> &followUp);
	void execute(float dt);
};

#endif //IMOVE_PONG_RESTARTBALLACTION_H