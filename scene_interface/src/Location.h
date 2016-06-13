#ifndef SCENEINTERFACE_Location_H
#define SCENEINTERFACE_Location_H

namespace scene_interface {
	class Location {
		public:
			Location(float x, float y);

			const float getX() const;
			const float getY() const;
		protected:
			float x,y;
	};
}

#endif //SCENEINTERFACE_Location_H
