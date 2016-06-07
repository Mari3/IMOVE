#ifndef SCENEINTERFACE_BOUNDARY_H
#define SCENEINTERFACE_BOUNDARY_H

#include "Vector2.h"

class Boundary {
private:

  Vector2 upper_left;
  Vector2 upper_right;
  Vector2 lower_left;
  Vector2 lower_right;

  // Parameters for equations
  float a1, a2, a3, a4;
  float b1, b2, b3, b4;

public:
  Boundary(Vector2 upleft, Vector2 upright, Vector2 lowleft, Vector2 lowright);
  bool inBounds(Vector2 location);
}
