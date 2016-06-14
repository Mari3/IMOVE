#ifndef IMOVE_BYSTANDERGRAVITYPOINTACTION_H
#define IMOVE_BYSTANDERGRAVITYPOINTACTION_H


#include <memory>
#include "../../Action.h"
#include "../LightPerson.h"
#include "../../Util/Timer.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../Configuration/LightTrailSceneConfiguration.h"

class BystanderGravityPointAction : public Action {
private:
    GravityPointRepository* gravityPoints;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<LightPerson> person;
    Timer timer;
    bool gravityPointActive;
    LightTrailSceneConfiguration config;
    void setLocation();
public:
    explicit BystanderGravityPointAction(std::shared_ptr<LightPerson> person, GravityPointRepository* gravityPoints,
    const LightTrailSceneConfiguration &config);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_BYSTANDERGRAVITYPOINTACTION_H
