#include <algorithm>

#include "Boundary.h"

Boundary::Boundary() {}

Boundary::Boundary(const Vector2& upleft, const Vector2& upright, const Vector2& lowleft, const Vector2& lowright) :
  upper_left(upleft), upper_right(upright), lower_left(lowleft), lower_right(lowright) {
    // Calculate parameters for equations for every edge
    if ((upper_right.y - upper_left.y) == 0) {
      a1 = upper_left.y;
      b1 = 0;
    } else {
      a1 = (upper_right.y - upper_left.y)/(upper_right.x - upper_left.x);
      b1 = (upper_left.x*a1 - upper_left.y);
    }

    if ((lower_right.x - upper_right.x) == 0) {
      a2 = upper_right.x;
      b2 = 0;
    } else {
      a2 = (lower_right.y - upper_right.y)/(lower_right.x - upper_right.x);
      b2 = (upper_right.x*a2 - upper_right.y);
    }

    if ((lower_left.y - lower_right.y) == 0) {
      a3 = lower_right.y;
      b3 = 0;
    } else {
      a3 = (lower_left.y - lower_right.y)/(lower_left.x - lower_right.x);
      b3 = (lower_right.x*a3 - lower_right.y);
    }

    if ((upper_left.x - lower_left.x) == 0) {
      a4 = lower_left.x;
      b4 = 0;
    } else {
      a4 = (upper_left.y - lower_left.y)/(upper_left.x - lower_left.x);
      b4 = (lower_left.x*a4 - lower_left.y);
    }
  }

Boundary::~Boundary() {}

bool Boundary::inBounds(Vector2 location) {
  // Perpendicular projection of the point on every edge
  float projection_edge1;
  float projection_edge2;
  float projection_edge3;
  float projection_edge4;

  // Calculate projection position on every edge
  if (b1 == 0) {
    projection_edge1 = a1;
  } else {
    projection_edge1 = ((a1*location.x) - b1);
  }

  if (b2 == 0) {
    projection_edge2 = a2;
  } else {
    projection_edge2 = ((location.y + b2)/a2);
  }

  if (b3 == 0) {
    projection_edge3 = a3;
  } else {
    projection_edge3 = ((a3*location.x) - b3);
  }

  if (b4 == 0) {
    projection_edge4 = a4;
  } else {
    projection_edge4 = ((location.y + b4)/a4);
  }

  // Check if location is within bounds
  if ((location.y > projection_edge1) && (location.y < projection_edge3)) {
    if ((location.x < projection_edge2) && (location.x > projection_edge4)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

/*--------------------
 * Getters
 * -----------------*/
const Vector2 Boundary::getUpperLeft() const {
	return this->upper_left;
}

const Vector2 Boundary::getUpperRight() const {
	return this->upper_right;
}

const Vector2 Boundary::getLowerLeft() const {
	return this->lower_left;
}

const Vector2 Boundary::getLowerRight() const {
	return this->lower_right;
}

const Boundary Boundary::createReorientedTopLeftBoundary() const {
	Vector2 origin(0, 0);

  // Calculate distance to origin for each corner
	float distance_upper_left  = origin.distance(upper_left );
	float distance_upper_right = origin.distance(upper_right);
	float distance_lower_left  = origin.distance(lower_left );
	float distance_lower_right = origin.distance(lower_right);

  // Find corner closest to origin
	float minimum_distance = std::min(
		std::min(
			distance_upper_left,
			distance_upper_right
		),
		std::min(
			distance_lower_left,
			distance_lower_right
		)
	);

	Boundary reoriented_boundary;
  
  // Rotate corners accordingly
	if (minimum_distance == distance_upper_left) {
		reoriented_boundary = Boundary(
			upper_left,
      upper_right,
      lower_left,
      lower_right
		);
	} else if (minimum_distance == distance_upper_right) {
		reoriented_boundary = Boundary(
      upper_right,
      lower_right,
			upper_left,
      lower_left
		);
	} else if (minimum_distance == distance_lower_left) {
		reoriented_boundary = Boundary(
      lower_left,
			upper_left,
      lower_right,
      upper_right
		);
	} else {
		reoriented_boundary = Boundary(
      lower_right,
      lower_left,
      upper_right,
			upper_left
		);
	}
	return reoriented_boundary;
}
