//
// Created by Wouter Posdijk on 31/05/16.
//

#include "LightSourceEffectAction.h"

LightSourceEffectAction::LightSourceEffectAction(std::shared_ptr<LightSource> source, LightTrailRepository *myLightTrails,
                                                 const LightTrailSceneConfiguration& config, sf::RenderTexture &texture
)
        : gravityPoint(source->getLocation(),source->getHue(),20000),
          myLightTrails(myLightTrails),
          config(config)
{
    util::Range range(-config.effect().source().placementRange,config.effect().source().placementRange);
    for(int i=0;i<config.effect().source().trailAmount;++i){
        myLightTrails->add(std::shared_ptr<LightTrail>(
                new LightTrail(
                        Vector2(source->getLocation().x+range.drawRandom(),source->getLocation().y+range.drawRandom()),
                        Vector2(range.drawRandom(),range.drawRandom()),
                        source->getHue().drawRandom()
                )
        ));
    }

    effects.push_back(std::unique_ptr<Effect>(
            static_cast<Effect*>(new LightTrailEffect(myLightTrails,config,texture))
    ));
}

bool LightSourceEffectAction::isDone(std::vector<Action *> &followUp) {
    //Never done
    return false;
}

void LightSourceEffectAction::execute(float dt) {
    myLightTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 force = gravityPoint.calculateForce(*trail,config);
        trail->applyForce(force,dt,config.trail().trail().speedCap,config.trail().sidesEnabled(),config.screenWidth(),config.screenHeight());
    });
}