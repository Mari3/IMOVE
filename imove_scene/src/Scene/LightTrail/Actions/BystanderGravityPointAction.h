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
    LightTrailRepository *myTrails, *globalTrails;
    LightSourceRepository* sources;
    std::shared_ptr<GravityPoint> gravityPoint;
    std::shared_ptr<LightPerson> person;
    Timer timer;
    sf::RenderTexture &texture;
    bool gravityPointActive;
    LightTrailSceneConfiguration config;
    void setLocation();
public:
    explicit BystanderGravityPointAction(std::shared_ptr<LightPerson> person,
                                             LightSourceRepository *sources,
                                             LightTrailRepository *myTrails,
                                             LightTrailRepository *globalTrails,
                                             const LightTrailSceneConfiguration &config,
                                             sf::RenderTexture &texture);

    bool isDone(std::vector<Action*> &followUp) override;

    void execute(float dt) override;


};


#endif //IMOVE_BYSTANDERGRAVITYPOINTACTION_H
