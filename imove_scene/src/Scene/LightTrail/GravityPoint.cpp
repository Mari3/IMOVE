#include "GravityPoint.h"

GravityPoint::GravityPoint(
	Vector2 location,
	util::Range hue,
	float gravity,
	float range,
	bool isColorHole
) :
	colorHole(isColorHole),
    location(location),
    hue(hue),
    gravity(gravity),
    range(range)
{

}

Vector2 GravityPoint::calculateForce(LightTrail trail, const LightTrailSceneConfiguration& config) {
    if(hue.contains(trail.hue)) { // If the hue of the light trail is in the hue-range of the gravity point
        Vector2 diff = location - trail.getLocation();
        float dist = diff.size();
        float proximityModifier = 1;

        if (dist < config.gravity().proximity().range) { // If the light trail is in a certain proximity to the gravity point
            // Decrease instead of increase the gravity the closer the trail gets
            // in order to cause orbit
            // proximityModifier = config.proximityModifier() * (dist/config.proximityRange()) * (dist/config.proximityRange());
            proximityModifier = config.gravity().proximity().modifier *
                    dist/config.gravity().proximity().range;
        }
        if(dist > 10 && (range < 0 || dist < range)) {
            // Add force that is inversely proportional to distance, like real gravity.
            return diff / dist / dist * proximityModifier * gravity;
        }
    }
    return Vector2(0,0);
}

bool GravityPoint::isColorHole() {
    return colorHole;
}






