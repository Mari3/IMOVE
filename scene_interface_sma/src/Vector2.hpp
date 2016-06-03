#ifndef SCENEINTERFACESMA_VECTOR2_H
#define SCENEINTERFACESMA_VECTOR2_H

#include <boost/interprocess/offset_ptr.hpp>

namespace scene_interface_sma {
	class Vector2 {
		public:
			gVector2(float x, float y);
		
			float getX() const;
			float getY() const;
	
		private:
			gfloat x,y;
	};
}

#endif //SCENEINTERFACESMA_VECTOR2_H
