#ifndef SCENEINTERFACE_VECTOR2_H
#define SCENEINTERFACE_VECTOR2_H

#include <boost/interprocess/offset_ptr.hpp>

namespace scene_interface {
	class Vector2 {
		public:
		  Vector2(float x, float y);
		
			float getX() const;
			float getY() const;
	
		private:
		  float x,y;
	};
}

#endif //SCENEINTERFACE_VECTOR2_H
