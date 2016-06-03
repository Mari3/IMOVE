#include "Vector2.hpp"

using namespace scene_interface_sma;

Vector2::Vector2(float x, float y) : x(x), y(y) {}

float Vector2::getX() const {
	return this->x;
}
float Vector2::getY() const {
	return this->y;
}
