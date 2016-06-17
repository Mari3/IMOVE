#ifndef SCENEINTERFACE_BOUNDARY_H
#define SCENEINTERFACE_BOUNDARY_H

#include "Vector2.h"
#include <iostream>

class Boundary {
private:

  // Coordinates of boundary corners
  Vector2 upper_left;
  Vector2 upper_right;
  Vector2 lower_left;
  Vector2 lower_right;

  // Parameters for equations
  float a1, a2, a3, a4;
  float b1, b2, b3, b4;

public:
  Boundary();
  Boundary(const Vector2& upleft, const Vector2& upright, const Vector2& lowleft, const Vector2& lowright);
  ~Boundary();
  bool inBounds(const Vector2& location);

  // Getters
	const Vector2 getUpperLeft() const;
	const Vector2 getUpperRight() const;
	const Vector2 getLowerLeft() const;
	const Vector2 getLowerRight() const;


  //Creates a Boundary from current coordinates and rotates so that top left is least amount of distance from origin on coordinate system
	const Boundary createReorientedTopLeftBoundary() const;
};

#endif // SCENEINTERFACE_BOUNDARY_H
