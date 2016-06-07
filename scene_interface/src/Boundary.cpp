
#include "Boundary.h"

Boundary::Boundary(Vector2 upleft, Vector2 upright, Vector2 lowleft, Vector2 lowright) :
  upper_left(upleft), upper_right(upright), lower_left(lowleft), lower_right(lowright) {
    a1 = (upper_right.y - upper_left.y)/(upper_right.x - upper_left.x);
    b1 = upper_left.x*a1;

    a2 = (lower_right.y - upper_right.y)/(lower_right.x - upper_right.x);
    b2 = upper_right.x*a2;

    a3 = (lower_left.y - lower_right.y)/(lower_left.x - lower_right.x);
    b3 = lower_right.x*a3;

    a4 = (upper_left.y - lower_left.y)/(upper_left.x - lower_left.x);
    b4 = lower_left.x*a4;
  }

bool Boundary::inBounds(Vector2 location) {
  if ((location.y < ((a1*location.x) - b1)) && (location.y > ((a3*location.x) - b3))) {
    if ((location.x < ((location.y - b2)/a2)) && (location.x > ((location.y - b4)/a4))) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}
