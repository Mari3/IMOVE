//
// Created by Wouter Posdijk on 24/05/16.
//

#ifndef IMOVE_LIGHTTRAILCONFIGURATION_H
#define IMOVE_LIGHTTRAILCONFIGURATION_H

#include <cstdint>
#include <string>
#include <vector>
#include "../Util/Range.h"

class LightTrailConfiguration {
private:
    // Screen size
    unsigned int _screenWidth, _screenHeight;

    // Light source hues
    std::vector<util::Range> _cornerHues;

    // Light sources
    float _sendOutDelay;
    int _trailCap;
    util::Range _sendOutSpeed;

    // Player gravitation
    float _participantGravity, _participantAntigravity, _participantGravityRange,
            _bystanderGravity, _bystanderGravityDelay, _bystanderGravityRange;

    // Other gravitation
    float _alternatingGravity, _gravityPointDelay, _alternatingGravityRange;

    // Orbiting
    float _proximityRange, _proximityModifier;

    // Sides
    bool _sidesEnabled;

    // Trail properties
    float _speedCap;
    int _trailThickness;

    // Display
    uint8_t _fade;

    // Mixing
    float _mixingSpeed, _mixingDistance, _mixingRevertTime;

    // Explosion
    float _explosionAntigravity, _explosionGravity, _explosionExTime, _explosionInTime;

public:


    LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight, const util::Range &_corner1Hue,
                            const util::Range &_corner2Hue, const util::Range &_corner3Hue,
                            const util::Range &_corner4Hue, float _sendOutDelay, int _trailCap, const util::Range &_sendOutSpeed,
                            float _participantGravity, float _participantAntigravity, float _participantGravityRange,
                            float _bystanderGravity, float _bystanderGravityDelay, float _bystanderGravityRange,
                            float _alternatingGravity, float _gravityPointDelay,
                            float _alternatingGravityRange, float _proximityRange,
                            float _proximityModifier, bool _sidesEnabled, float _speedCap, int _trailThickness, uint8_t _fade,
                            float _mixingSpeed, float _mixingDistance, float _mixingRevertTime, float _explosionAntigravity,
                            float _explosionGravity, float _explosionExTime, float _explosionInTime
    );

    static LightTrailConfiguration readFromFile(char* fileName);

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const std::vector<util::Range> & cornerHues() const;

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

    float mixingSpeed() const;

    float mixingDistance() const;

    float mixingRevertTime() const;

    float explosionAntigravity() const;

    float explosionGravity() const;

    float explosionExTime() const;

    float explosionInTime() const;

    float participantGravityRange() const;

    float bystanderGravityRange() const;

    float alternatingGravityRange() const;
};


#endif //IMOVE_LIGHTTRAILCONFIGURATION_H
