#ifndef IMOVE_LIGHTPERSON_H
#define IMOVE_LIGHTPERSON_H

#include <list>

#include "../../../../scene_interface/src/Person.h"
#include "../../../../imove_imp/src/Vector2.h"
#include "../Util/Range.h"

class LightPerson{
private:
    Vector2 location;
    std::list<Vector2> previousLocations;
    unsigned int id;
public:
    bool isColorHole;
    scene_interface::Person::PersonType person_type;
    scene_interface::Person::MovementType movement_type;
    LightPerson(const Vector2 &location, unsigned int id, scene_interface::Person::PersonType person_type, scene_interface::Person::MovementType movement_type, util::Range hue);

    void shiftHue(float shift);
    void setLocation(Vector2 newLocation);
    Vector2 getLocation();
    unsigned int getId();
    util::Range hue;
};


#endif //IMOVE_LIGHTPERSON_H
