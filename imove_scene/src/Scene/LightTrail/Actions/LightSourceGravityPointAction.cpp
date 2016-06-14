//
// Created by Wouter Posdijk on 03/06/16.
//

#include <cmath>
#include "LightSourceGravityPointAction.h"

LightSourceGravityPointAction::LightSourceGravityPointAction(LightPersonRepository *lightPeople, GravityPointRepository *gravityPoints,
                                                             const LightTrailSceneConfiguration &config)
        : lightPeople(lightPeople),
          gravityPoints(gravityPoints),
          config(config) {
    float gravity = config.gravity().lightSource().gravity;
    gPoints[0] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,0),config.trail().cornerHues()[0],gravity));
    gPoints[1] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),0),config.trail().cornerHues()[1],gravity));
    gPoints[2] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(0,config.screenHeight()),config.trail().cornerHues()[2],gravity));
    gPoints[3] = std::shared_ptr<GravityPoint>(new GravityPoint(Vector2(config.screenWidth(),config.screenHeight()),config.trail().cornerHues()[3],gravity));

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
        float highest = config.trail().cornerHues()[i].start;
        float lowest = config.trail().cornerHues()[i].end;
        util::Range lowestRange(highest,lowest,true);
        util::Range highestRange(highest,lowest,true);
        bool noGpoint = false;
        gravityPoints->for_each([&](std::shared_ptr<GravityPoint> gPoint){
            if(gPoint != gPoints[i] && gPoint->gravity > 0 && !gPoint->isColorHole()) {
                float start = gPoint->hue.start;
                float end = gPoint->hue.end;
                if (start == config.trail().cornerHues()[i].start ||
                    (gPoint->hue.contains(config.trail().cornerHues()[i].start) &&
                     gPoint->hue.contains(config.trail().cornerHues()[i].end))) {
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
            gPoints[i]->gravity = config.gravity().lightSource().gravity;
            gPoints[i]->hue.start = highest;
            gPoints[i]->hue.end = lowest;
        }

    }
}