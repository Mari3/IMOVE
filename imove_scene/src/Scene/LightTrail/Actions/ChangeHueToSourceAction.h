//
// Created by Wouter Posdijk on 07/06/16.
//

#ifndef IMOVE_CHANGEHUETOSOURCEACTION_H
#define IMOVE_CHANGEHUETOSOURCEACTION_H


#include <memory>
#include "../LightSource.h"
#include "../LightPerson.h"
#include "../../Action.h"

class ChangeHueToSourceAction : public Action {
private:
    float progressLeft;
    std::shared_ptr<LightPerson> person;
public:
    ChangeHueToSourceAction(std::shared_ptr<LightPerson> person, std::shared_ptr<LightSource> source);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_CHANGEHUETOSOURCEACTION_H
