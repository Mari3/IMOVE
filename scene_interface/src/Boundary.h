#ifndef SCENEINTERFACE_BOUNDARY_H
#define SCENEINTERFACE_BOUNDARY_H

#include "Vector2.h"

class Boundary {
private:

  scene_interface::Vector2 upper_left;
  scene_interface::Vector2 upper_right;
  scene_interface::Vector2 lower_left;
  scene_interface::Vector2 lower_right;

  // Parameters for equations
  float a1, a2, a3, a4;
  float b1, b2, b3, b4;

public:
  Boundary();
  Boundary(scene_interface::Vector2 upleft, scene_interface::Vector2 upright, scene_interface::Vector2 lowleft, scene_interface::Vector2 lowright);
  ~Boundary();
  bool inBounds(scene_interface::Vector2 location);

	const scene_interface::Vector2 getUpperLeft() const;
	const scene_interface::Vector2 getUpperRight() const;
	const scene_interface::Vector2 getLowerLeft() const;
	const scene_interface::Vector2 getLowerRight() const;
};

#endif // SCENEINTERFACE_BOUNDARY_H
