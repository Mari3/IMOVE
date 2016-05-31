#include "Vector2.hpp"

using namespace scene_interface;

scene_interface::Vector2::Vector2(float x, float y) : x(x), y(y) {}

float scene_interface::Vector2::getX() const {
	return this->x;
}
float scene_interface::Vector2::getY() const {
	return this->y;
}
