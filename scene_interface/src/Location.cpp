#include "Location.h"

using namespace scene_interface;

Location::Location(float x, float y) : x(x), y(y) { }

const float Location::getX() const {
	return this->x;
}
const float Location::getY() const {
	return this->y;
}
