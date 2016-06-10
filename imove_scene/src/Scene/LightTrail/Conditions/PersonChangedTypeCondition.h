#ifndef IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
#define IMOVE_PERSONTURNEDBYSTANDERCONDITION_H

#include <vector>
#include <SFML/Graphics/RenderTexture.hpp>
#include "../Repositories/LightPersonMapRepository.h"
#include "../../Condition.h"
#include "../Repositories/LightsSceneRepositories.h"
#include "../LightTrailConfiguration.h"
#include "../../../../../scene_interface/src/Person.h"

class PersonChangedTypeCondition : public Condition {
private:
    LightPersonRepository* lightPeople;
    GravityPointRepository* gravityPoints;
    std::map<int,scene_interface::Person::PersonType> oldPersonType;
    std::map<int,scene_interface::Person::MovementType> oldMovementType;
    LightTrailRepository* lightTrails;
    LightSourceRepository* lightSources;
    LightTrailConfiguration config;
    sf::RenderTexture& texture;
public:
    PersonChangedTypeCondition(LightPersonRepository *lightPeople,
                                   GravityPointRepository *gravityPoints,
                                   LightTrailRepository *lightTrails,
                                   LightSourceRepository *lightSources,
                                   const LightTrailConfiguration &config,
                                   sf::RenderTexture &texture);
    int check(float dt, std::vector<Action*> &actions) override;
};


#endif //IMOVE_PERSONTURNEDBYSTANDERCONDITION_H
