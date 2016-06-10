#include <boost/interprocess/offset_ptr.hpp>

namespace scene_interface_sma {
	class Location {
		public:
			Location(float x, float y);
		
			float getX() const;
			float getY() const;
	
		private:
			float x,y;
	};
}
