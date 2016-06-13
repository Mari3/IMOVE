//
// Created by Wouter Posdijk on 30/05/16.
//

#ifndef IMOVE_MIXINGACTION_H
#define IMOVE_MIXINGACTION_H


#include "../../Action.h"
#include "../LightPerson.h"
#include "../Configuration/LightTrailConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Effects/MixingEffect.h"

class MixingAction : public Action {
private:
    std::shared_ptr<LightPerson> person1, person2;
    float progress;
    LightTrailConfiguration config;
    LightTrailRepository* trails;
    GravityPointRepository* gravityPoints;
    bool mixingComplete = false;
    MixingEffect effect;
public:
    MixingAction(std::shared_ptr<LightPerson> person1, std::shared_ptr<LightPerson> person2, LightTrailRepository* trails,
                 GravityPointRepository* gravityPoints, const LightTrailConfiguration& config);
    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;

    void draw(sf::RenderTarget &target) override;


    static void shift(LightTrailRepository* trails, Vector2 location, util::Range& hue, float amount);
};


#endif //IMOVE_MIXINGACTION_H
