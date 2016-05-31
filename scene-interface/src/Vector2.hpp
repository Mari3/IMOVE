#ifndef SCENEINTERFACE_VECTOR2_H
#define SCENEINTERFACE_VECTOR2_H

class Vector2 {
	public:
	  Vector2(float x, float y);
	
		float getX() const;
		float getY() const;

	private:
	  float x,y;
};

#endif //SCENEINTERFACE_VECTOR2_H
