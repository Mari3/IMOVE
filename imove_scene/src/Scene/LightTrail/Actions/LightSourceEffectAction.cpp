//
// Created by Wouter Posdijk on 31/05/16.
//

#include "LightSourceEffectAction.h"

LightSourceEffectAction::LightSourceEffectAction(std::shared_ptr<LightSource> source, LightTrailRepository *myLightTrails,
                                                 const LightTrailConfiguration& config
)
        : gravityPoint(source->getLocation(),source->getHue(),20000),
          myLightTrails(myLightTrails),
          config(config)
{
    util::Range range(-40,40);
    for(int i=0;i<10;++i){
        myLightTrails->add(std::shared_ptr<LightTrail>(
                new LightTrail(
                        Vector2(source->getLocation().x+range.drawRandom(),source->getLocation().y+range.drawRandom()),
                        Vector2(range.drawRandom(),range.drawRandom()),
                        source->getHue().drawRandom()
                )
        ));
    }
}

bool LightSourceEffectAction::isDone(std::vector<Action *> &followUp) {
    //Never done
    return false;
}

void LightSourceEffectAction::execute(float dt) {
    myLightTrails->for_each([&](std::shared_ptr<LightTrail> trail){
        Vector2 force = gravityPoint.calculateForce(*trail,config);
        trail->applyForce(force,dt,config.speedCap(),config.sidesEnabled(),config.screenWidth(),config.screenHeight());
    });
}
