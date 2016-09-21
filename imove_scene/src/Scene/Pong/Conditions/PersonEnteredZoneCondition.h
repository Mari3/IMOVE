#ifndef IMOVE_PERSONENTEREDZONECONDITION_H
#define IMOVE_PERSONENTEREDZONECONDITION_H

#include <memory>
#include "../../Util/Repository.h"
#include <vector>
#include "../../Condition.h"
#include "../PongScene.h"
#include "../Actions/ControlPaddleAction.h"
#include "../PongConfiguration.h"


class PersonEnteredZoneCondition : public Condition {
private:
	Repository<PongPerson>* people;
	std::shared_ptr<Paddle> p1,p2;
	PongConfiguration config;
public:
	PersonEnteredZoneCondition(Repository<PongPerson>* people,
		std::shared_ptr<Paddle> p1, std::shared_ptr<Paddle> p2,
		PongConfiguration config);
	int check(float dt, std::vector<Action*> &actions) override;
};

#endif //IMOVE_PERSONENTEREDZONECONDITION_H