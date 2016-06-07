#ifndef IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
#define IMOVE_PARTICIPANTGRAVITYPOINTACTION_H


#include <memory>
#include "../../Action.h"
#include "../LightPerson.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"

class ParticipantGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<GravityPoint> antigravityPoint;
    std::shared_ptr<LightPerson> person;
    LightTrailConfiguration config;
    void setLocation();
public:
    explicit ParticipantGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
    const LightTrailConfiguration& config);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
