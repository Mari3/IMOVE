#ifndef IMOVE_LIGHTPERSON_H
#define IMOVE_LIGHTPERSON_H

#include <list>

#include "../../../../scene_interface/src/Vector2.h"
#include "../../../../scene_interface/src/Person.h"
#include "../Util/Range.h"

class LightPerson{
private:
    Vector2 location;
    std::list<Vector2> previousLocations;
    unsigned int id;
public:
    scene_interface::Person::PersonType type;
    LightPerson(const Vector2 &location, unsigned int id, scene_interface::Person::PersonType type, util::Range hue);
    void shiftHue(float shift);
    void setLocation(Vector2 newLocation);
    Vector2 getLocation();
    unsigned int getId();
    util::Range hue;
};


#endif //IMOVE_LIGHTPERSON_H
