
#include "Boundary.h"

Boundary::Boundary() {}

Boundary::Boundary(Vector2 upleft, Vector2 upright, Vector2 lowleft, Vector2 lowright) :
  upper_left(upleft), upper_right(upright), lower_left(lowleft), lower_right(lowright) {
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
  float projection_edge1;
  float projection_edge2;
  float projection_edge3;
  float projection_edge4;

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
