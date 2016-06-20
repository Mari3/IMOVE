//
// Created by Wouter Posdijk on 10/06/16.
//

#ifndef IMOVE_INITIATEPARTICIPANTACTION_H
#define IMOVE_INITIATEPARTICIPANTACTION_H


#include "../Repositories/LightsSceneRepositories.h"
#include "../../Action.h"
#include "../Effects/LightTrailEffect.h"

// Sends a certain amount of trails to a person,
// ignoring the rest of the scene.
class InitiateParticipantAction : public Action {
private:
    LightTrailRepository* globalTrails;
    LightSourceRepository* sources;
    std::shared_ptr<LightPerson> person;
    GravityPoint gravityPoint;
    LightTrailSceneConfiguration config;
    bool init = true;
public:
    InitiateParticipantAction(LightTrailRepository *globalTrails,
                              LightSourceRepository *sources, const std::shared_ptr<LightPerson> &person,
                              const LightTrailSceneConfiguration& config, sf::RenderTexture &texture
        );

    bool isDone(std::vector<Action *> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_INITIATEPARTICIPANTACTION_H
