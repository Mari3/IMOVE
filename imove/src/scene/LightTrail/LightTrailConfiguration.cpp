//
// Created by Wouter Posdijk on 24/05/16.
//

#include <opencv2/opencv.hpp>
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
                                                 const util::Range &_corner4Hue, float _sendOutDelay, int _trailCap, const util::Range &_sendOutSpeed,
                                                 float _participantGravity, float _participantAntigravity, float _bystanderGravity,
                                                 float _alternatingGravity, float _gravityPointDelay, float _proximityRange,
                                                 float _proximityModifier, bool _sidesEnabled, float _speedCap, int _trailThickness, uint8_t _fade)
        : _screenWidth(_screenWidth), _screenHeight(_screenHeight), _corner1Hue(_corner1Hue),
          _corner2Hue(_corner2Hue), _corner3Hue(_corner3Hue), _corner4Hue(_corner4Hue),
          _sendOutDelay(_sendOutDelay), _trailCap(_trailCap), _sendOutSpeed(_sendOutSpeed), _participantGravity(_participantGravity),
          _participantAntigravity(_participantAntigravity), _bystanderGravity(_bystanderGravity),
          _alternatingGravity(_alternatingGravity), _gravityPointDelay(_gravityPointDelay),
          _proximityRange(_proximityRange), _proximityModifier(_proximityModifier), _sidesEnabled(_sidesEnabled),
          _speedCap(_speedCap), _trailThickness(_trailThickness), _fade(_fade) { }

float LightTrailConfiguration::bystanderGravityDelay() const {
    return _bystanderGravityDelay;
}

const util::Range &LightTrailConfiguration::sendOutSpeed() const {
    return _sendOutSpeed;
}

LightTrailConfiguration LightTrailConfiguration::readFromFile(char *fileName) {
    cv::FileStorage fs;
    fs.open(fileName, cv::FileStorage::READ);

    cv::Size resolution;
    cv::Vec2f topLeftRange;
    cv::Vec2f topRightRange;
    cv::Vec2f bottomRightRange;
    cv::Vec2f bottomLeftRange;
    cv::Vec2f sendOutSpeed;
    float sendOutDelay;
    int trailCap;
    float participantGravity, participantAntiGravity, bystanderGravity,
            bystanderGravityDelay, alternatingGravity, alternatingGravityDelay,
            proximityRange, proximityModifier, speedCap;
    bool sidesEnabled;
    int fadeint, trailThickness;

    fs["Resolution"] >> resolution;
    fs["TopLeftHue"] >> topLeftRange;
    fs["TopRightHue"] >> topRightRange;
    fs["BottomRightHue"] >> bottomRightRange;
    fs["BottomLeftHue"] >> bottomLeftRange;
    fs["SendOutDelay"] >> sendOutDelay;
    fs["SendOutSpeed"] >> sendOutSpeed;
    fs["TrailCap"] >> trailCap;
    fs["ParticipantGravity"] >> participantGravity;
    fs["ParticipantAntiGravity"] >> participantAntiGravity;
    fs["BystanderGravity"] >> bystanderGravity;
    fs["BystanderGravityDelay"] >> bystanderGravityDelay;
    fs["AlternatingGravity"] >> alternatingGravity;
    fs["AlternatingGravityDelay"] >> alternatingGravityDelay;
    fs["ProximityRange"] >> proximityRange;
    fs["ProximityModifier"] >> proximityModifier;
    fs["SidesEnabled"] >> sidesEnabled;
    fs["SpeedCap"] >> speedCap;
    fs["Fade"] >> fadeint;
    fs["TrailThickness"] >> trailThickness;

    uint8_t fade = static_cast<uint8_t>(fadeint > 255 ? 255 : fadeint);

    unsigned int w = static_cast<unsigned int>(resolution.width);
    unsigned int h = static_cast<unsigned int>(resolution.height);

    return LightTrailConfiguration(w,h,
                                   util::Range(topLeftRange.val[0],topLeftRange.val[1],true),
                                   util::Range(topRightRange.val[0],topRightRange.val[1],true),
                                   util::Range(bottomLeftRange.val[0],bottomLeftRange.val[1],true),
                                   util::Range(bottomRightRange.val[0],bottomRightRange.val[1],true),
                                   sendOutDelay, trailCap,
                                   util::Range(sendOutSpeed.val[0],sendOutSpeed.val[1]),
                                   participantGravity,participantAntiGravity,
                                   bystanderGravity,alternatingGravity,
                                   alternatingGravityDelay,proximityRange,proximityModifier,
                                   sidesEnabled,speedCap,trailThickness,fade
    );
}

int LightTrailConfiguration::trailThickness() const {
    return _trailThickness;
}