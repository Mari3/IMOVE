#ifndef IMOVE_PONG_SCOREDCONDITION_H
#define IMOVE_PONG_SCOREDCONDITION_H

#include "../../Condition.h"
#include "../PongScene.h"
#include "../PongConfiguration.h"

class ScoredCondition : public Condition {
private:
	std::shared_ptr<Ball> ball;
	std::shared_ptr<Score> score;
	PongConfiguration config;
public:
	ScoredCondition(std::shared_ptr<Ball> ball, std::shared_ptr<Score> score, PongConfiguration config);
	int check(float dt, std::vector<Action*> &actions) override;
};

#endif //IMOVE_PONG_SCOREDCONDITION_H