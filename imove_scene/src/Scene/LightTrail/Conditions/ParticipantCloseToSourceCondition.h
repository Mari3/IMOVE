//
// Created by Wouter Posdijk on 07/06/16.
//

#ifndef IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H
#define IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H


#include "../Configuration/LightTrailSceneConfiguration.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../../Condition.h"

class ParticipantCloseToSourceCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    LightSourceRepository* lightSources;
    LightSourceConfig config;
public:

    ParticipantCloseToSourceCondition(LightPersonRepository *lightPeople,
                                          LightSourceRepository *lightSources,
                                          const LightSourceConfig &config);

    int check(float dt, std::vector<Action *> &actions) override;


};


#endif //IMOVE_PARTICIPANTCLOSETOSOURCECONDITION_H
