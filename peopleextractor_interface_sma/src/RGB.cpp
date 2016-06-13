#include "Image.hpp"

using namespace peopleextractor_interface_sma;

RGB::RGB(const unsigned char red, const unsigned char green, const unsigned char blue) : red(red), green(green), blue(blue) { }

const unsigned char RGB::getRed() const {
	return this->red;
}
const unsigned char RGB::getGreen() const {
	return this->green;
}
const unsigned char RGB::getBlue() const {
	return this->blue;
}
