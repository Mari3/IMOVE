//
// Created by Wouter Posdijk on 11/05/16.
//

#include "Vector2.h"
#include "math.h"

Vector2::Vector2(float x, float y) : x(x), y(y)
{
}

float Vector2::distance(Vector2 other) {
    return (other-*this).size();
}

Vector2 Vector2::operator-(const Vector2 &v) {
    return Vector2(x-v.x, y-v.y);
}

Vector2 Vector2::operator+(const Vector2 &v) {
    return Vector2(x+v.x, y+v.y);
}

float Vector2::size() {
    return (float)sqrt(x*x+y*y);
}

Vector2 Vector2::operator/(const float &v) {
    return Vector2(x/v, y/v);
}

void Vector2::operator+=(const Vector2 &v) {
    x += v.x;
    y += v.y;
}

Vector2 Vector2::operator*(const float &v) {
    return Vector2(x*v,y*v);
}

float Vector2::angle(Vector2 other) {
    float cosangle = (x*other.x+y*other.y)/size()/other.size();
    return acosf(cosangle)/(float)M_PI*180.f;
}


