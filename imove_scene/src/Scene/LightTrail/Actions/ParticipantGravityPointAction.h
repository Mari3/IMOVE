#ifndef IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
#define IMOVE_PARTICIPANTGRAVITYPOINTACTION_H


#include <memory>
#include "../../Action.h"
#include "../LightPerson.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"

using namespace scene_interface;

class ParticipantGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<LightPerson> person;
    void setLocation();
public:
    explicit ParticipantGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
    const LightTrailConfiguration& config);

    bool isDone(Action *&followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_PARTICIPANTGRAVITYPOINTACTION_H
