//
// Created by Wouter Posdijk on 16/06/16.
//

#ifndef IMOVE_REMOVETRAILSACTION_H
#define IMOVE_REMOVETRAILSACTION_H


#include "../Repositories/LightsSceneRepositories.h"
#include "../../Action.h"

class RemoveTrailsAction : public Action {
private:
    std::shared_ptr<LightPerson> person;
    LightTrailRepository *trails;
    LightTrailSceneConfiguration config;
public:
    RemoveTrailsAction(const std::shared_ptr<LightPerson> &person, LightTrailRepository *trails,
                       const LightTrailSceneConfiguration &config);

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_REMOVETRAILSACTION_H
