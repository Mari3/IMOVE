//
// Created by Wouter Posdijk on 12/06/16.
//

#include "StarEffectAction.h"

bool StarEffectAction::isDone(std::vector<Action *> &followUp) {
    return false;
}

void StarEffectAction::execute(float dt) {
    effect.update(dt);
}

void StarEffectAction::draw(sf::RenderTarget &target) {
    effect.draw(target);
}

StarEffectAction::StarEffectAction(const LightTrailSceneConfiguration &config) : effect(config) {

}

