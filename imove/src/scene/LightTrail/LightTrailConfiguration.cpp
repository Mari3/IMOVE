//
// Created by Wouter Posdijk on 24/05/16.
//

#include "LightTrailConfiguration.h"

unsigned int LightTrailConfiguration::screenWidth() const {
    return _screenWidth;
}

unsigned int LightTrailConfiguration::screenHeight() const {
    return _screenHeight;
}

const util::Range &LightTrailConfiguration::corner1Hue() const {
    return _corner1Hue;
}

const util::Range &LightTrailConfiguration::corner2Hue() const {
    return _corner2Hue;
}

const util::Range &LightTrailConfiguration::corner3Hue() const {
    return _corner3Hue;
}

const util::Range &LightTrailConfiguration::corner4Hue() const {
    return _corner4Hue;
}

float LightTrailConfiguration::sendOutDelay() const {
    return _sendOutDelay;
}

int LightTrailConfiguration::trailCap() const {
    return _trailCap;
}

float LightTrailConfiguration::participantGravity() const {
    return _participantGravity;
}

float LightTrailConfiguration::participantAntigravity() const {
    return _participantAntigravity;
}

float LightTrailConfiguration::bystanderGravity() const {
    return _bystanderGravity;
}

float LightTrailConfiguration::alternatingGravity() const {
    return _alternatingGravity;
}

float LightTrailConfiguration::gravityPointDelay() const {
    return _gravityPointDelay;
}

float LightTrailConfiguration::proximityRange() const {
    return _proximityRange;
}

float LightTrailConfiguration::proximityModifier() const {
    return _proximityModifier;
}

bool LightTrailConfiguration::sidesEnabled() const {
    return _sidesEnabled;
}

float LightTrailConfiguration::speedCap() const {
    return _speedCap;
}

uint8_t LightTrailConfiguration::fade() const {
    return _fade;
}

LightTrailConfiguration::LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight, const util::Range &_corner1Hue,
                                                 const util::Range &_corner2Hue, const util::Range &_corner3Hue,
                                                 const util::Range &_corner4Hue, float _sendOutDelay, int _trailCap,
                                                 float _participantGravity, float _participantAntigravity, float _bystanderGravity,
                                                 float _alternatingGravity, float _gravityPointDelay, float _proximityRange,
                                                 float _proximityModifier, bool _sidesEnabled, float _speedCap, uint8_t _fade)
        : _screenWidth(_screenWidth), _screenHeight(_screenHeight), _corner1Hue(_corner1Hue),
          _corner2Hue(_corner2Hue), _corner3Hue(_corner3Hue), _corner4Hue(_corner4Hue),
          _sendOutDelay(_sendOutDelay), _trailCap(_trailCap), _participantGravity(_participantGravity),
          _participantAntigravity(_participantAntigravity), _bystanderGravity(_bystanderGravity),
          _alternatingGravity(_alternatingGravity), _gravityPointDelay(_gravityPointDelay),
          _proximityRange(_proximityRange), _proximityModifier(_proximityModifier), _sidesEnabled(_sidesEnabled),
          _speedCap(_speedCap), _fade(_fade) { }

float LightTrailConfiguration::bystanderGravityDelay() const {
    return _bystanderGravityDelay;
}