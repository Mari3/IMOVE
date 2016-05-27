//
// Created by Wouter Posdijk on 24/05/16.
//

#ifndef IMOVE_LIGHTTRAILCONFIGURATION_H
#define IMOVE_LIGHTTRAILCONFIGURATION_H

#include <cstdint>
#include <string>
#include "../Util/Range.h"

class LightTrailConfiguration {
private:
    // Screen size
    unsigned int _screenWidth, _screenHeight;

    // Light source hues
    util::Range _corner1Hue, _corner2Hue, _corner3Hue, _corner4Hue;

    // Light sources
    float _sendOutDelay;
    int _trailCap;
    util::Range _sendOutSpeed;

    // Player gravitation
    float _participantGravity, _participantAntigravity, _bystanderGravity, _bystanderGravityDelay;

    // Other gravitation
    float _alternatingGravity, _gravityPointDelay;

    // Orbiting
    float _proximityRange, _proximityModifier;

    // Sides
    bool _sidesEnabled;

    // Trail properties
    float _speedCap;
    int _trailThickness;

    // Display
    uint8_t _fade;

public:


    LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight, const util::Range &_corner1Hue,
                            const util::Range &_corner2Hue, const util::Range &_corner3Hue,
                            const util::Range &_corner4Hue, float _sendOutDelay, int _trailCap, const util::Range &_sendOutSpeed,
                            float _participantGravity, float _participantAntigravity, float _bystanderGravity, float _bystanderGravityDelay,
                            float _alternatingGravity, float _gravityPointDelay, float _proximityRange,
                            float _proximityModifier, bool _sidesEnabled, float _speedCap, int _trailThickness, uint8_t _fade);

    static LightTrailConfiguration readFromFile(char* fileName);

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const util::Range & corner1Hue() const;

    const util::Range & corner2Hue() const;

    const util::Range & corner3Hue() const;

    const util::Range & corner4Hue() const;

    float sendOutDelay() const;

    int trailCap() const;

    float participantGravity() const;

    float participantAntigravity() const;

    float bystanderGravity() const;

    float bystanderGravityDelay() const;

    float alternatingGravity() const;

    float gravityPointDelay() const;

    float proximityRange() const;

    float proximityModifier() const;

    bool sidesEnabled() const;

    float speedCap() const;

    uint8_t fade() const;

    const util::Range & sendOutSpeed() const;

    int trailThickness() const;
};


#endif //IMOVE_LIGHTTRAILCONFIGURATION_H
