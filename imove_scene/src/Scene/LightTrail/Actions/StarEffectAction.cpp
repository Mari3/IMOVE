//
// Created by Wouter Posdijk on 12/06/16.
//

#include "StarEffectAction.h"

bool StarEffectAction::isDone(std::vector<Action *> &followUp) {
    return false;
}

void StarEffectAction::execute(float dt) {
}

StarEffectAction::StarEffectAction(const LightTrailSceneConfiguration &config) {
    effects.push_back(std::unique_ptr<Effect>(
        static_cast<Effect*>(new StarEffect(config))
    ));
}

