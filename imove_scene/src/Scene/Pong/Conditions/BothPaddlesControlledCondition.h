#ifndef IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H
#define IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H

#include <memory>
#include "../../Util/Repository.h"
#include <vector>
#include "../../Condition.h"
#include "../PongScene.h"
#include "../Actions/ControlPaddleAction.h"
#include "../PongConfiguration.h"


class BothPaddlesControlledCondition : public Condition {
private:
	std::shared_ptr<Paddle> p1,p2;
	bool gameStarted = false;
	// PongConfiguration config;
public:
	BothPaddlesControlledCondition(std::shared_ptr<Paddle> p1,
    std::shared_ptr<Paddle> p2/*, PongConfiguration config*/);
	int check(float dt, std::vector<Action*> &actions) override;
};

#endif //IMOVE_BOTHPADDLESCONTROLLEDCONDITION_H
