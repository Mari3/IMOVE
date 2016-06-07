//
// Created by Wouter Posdijk on 03/06/16.
//

#include <cmath>
#include "LightSourceGravityPointAction.h"

LightSourceGravityPointAction::LightSourceGravityPointAction(LightPersonRepository *lightPeople, GravityPointRepository *gravityPoints,
                                                             const LightTrailConfiguration &config)
        : lightPeople(lightPeople),
          gravityPoints(gravityPoints),
          config(config) {
    gPoints[0] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),config.cornerHues()[0],500000));
    gPoints[1] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),0),config.cornerHues()[1],500000));
    gPoints[2] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,config.screenHeight()),config.cornerHues()[2],500000));
    gPoints[3] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),config.screenHeight()),config.cornerHues()[3],500000));

    execute(0);

    for(int i=0;i<4;++i){
        gravityPoints->add(gPoints[i]);
    }
}

bool LightSourceGravityPointAction::isDone(std::vector<Action *> &followUp) {
    return false;
}

void LightSourceGravityPointAction::execute(float dt) {
    for(int i=0;i<4;++i){
        float highest = config.cornerHues()[i].start;
        float lowest = config.cornerHues()[i].end;
        util::Range lowestRange(highest,lowest,true);
        util::Range highestRange(highest,lowest,true);
        bool noGpoint = false;
        gravityPoints->for_each([&](std::shared_ptr<GravityPoint> gPoint){
            if(gPoint != gPoints[i] && gPoint->gravity > 0 && !gPoint->isColorHole()) {
                float start = gPoint->hue.start;
                float end = gPoint->hue.end;
                if (start == config.cornerHues()[i].start ||
                    (gPoint->hue.contains(config.cornerHues()[i].start) &&
                     gPoint->hue.contains(config.cornerHues()[i].end))) {
                    noGpoint = true;
                } else {
                    if (lowestRange.contains(start)) {
                        lowest = start;
                        lowestRange.end = start;
                    }
                    else if (highestRange.contains(end)) {
                        highest = end;
                        highestRange.start = end;
                    }
                }
            }
        });
        if(!lowestRange.contains(highest) || noGpoint){
            gPoints[i]->gravity = 0;
        }else{
            gPoints[i]->gravity = 500000;
            gPoints[i]->hue.start = highest;
            gPoints[i]->hue.end = lowest;
        }

    }
}