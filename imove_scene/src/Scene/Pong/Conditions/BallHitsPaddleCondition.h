#ifndef IMOVE_PONG_BALLHITSPADDLECONDITION_H
#define IMOVE_PONG_BALLHITSPADDLECONDITION_H

#include "../../Condition.h"
#include "../PongScene.h"
#include "../PongConfiguration.h"

class BallHitsPaddleCondition : public Condition {
private:
	std::shared_ptr<Paddle> p1,p2;
	std::shared_ptr<Ball> ball;
	bool checkPaddle(std::shared_ptr<Paddle> p);
	PongConfiguration config;
public:
	BallHitsPaddleCondition(std::shared_ptr<Paddle> p1, std::shared_ptr<Paddle> p2,
		std::shared_ptr<Ball> ball, PongConfiguration config);
	int check(float dt, std::vector<Action*> &actions) override;
};

#endif //IMOVE_PONG_BALLHITSPADDLECONDITION_H