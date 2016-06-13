#include "Location.hpp"

using namespace scene_interface_sma;

Location::Location(float x, float y) : x(x), y(y) {}

float Location::getX() const {
	return this->x;
}
float Location::getY() const {
	return this->y;
}
