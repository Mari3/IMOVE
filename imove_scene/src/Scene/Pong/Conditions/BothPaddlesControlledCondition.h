#ifndef IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H
#define IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H

#include <memory>
#include "../../Util/Repository.h"
#include <vector>
#include "../../Condition.h"
#include "../PongScene.h"
#include "../Actions/RestartBallAction.h"
#include "../PongConfiguration.h"


class BothPaddlesControlledCondition : public Condition {
private:
	std::shared_ptr<Paddle> p1,p2;
	PongConfiguration config;
	std::shared_ptr<Ball> ball;
	bool gameStarted = false;
	std::shared_ptr<Score> score;

	int interactionTimer = 0;
public:
	BothPaddlesControlledCondition(std::shared_ptr<Paddle> p1,
    std::shared_ptr<Paddle> p2, PongConfiguration config,
		std::shared_ptr<Ball> ball, std::shared_ptr<Score> score);
	int check(float dt, std::vector<Action*> &actions) override;
};

#endif //IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H
