//
// Created by Wouter Posdijk on 07/06/16.
//

#ifndef IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H
#define IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H


#include "../Configuration/LightTrailConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class ParticipantCloseToSourceCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    LightSourceRepository* lightSources;
    LightTrailConfiguration config;
public:

    ParticipantCloseToSourceCondition(LightPersonRepository *lightPeople,
                                          LightSourceRepository *lightSources,
                                          const LightTrailConfiguration &config);

    int check(float dt, std::vector<Action *> &actions) override;


};


#endif //IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H
