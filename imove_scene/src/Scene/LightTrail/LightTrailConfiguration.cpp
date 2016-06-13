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

LightTrailConfiguration::LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight,
                                                 const util::Range &_corner1Hue, const util::Range &_corner2Hue,
                                                 const util::Range &_corner3Hue, const util::Range &_corner4Hue,
                                                 float _sendOutDelay, int _trailCap,
                                                 const util::Range &_sendOutSpeed, float _participantGravity,
                                                 float _participantAntigravity, float _participantGravityRange,
                                                 float _participantGravityDistance, float _bystanderGravityDelay,
                                                 float _bystanderGravityRange, float _alternatingGravity,
                                                 float _gravityPointDelay, float _alternatingGravityRange,
<<<<<<< a433a11f63b8a09e98546efa02c2aedebd785d20
                                                 float _proximityRange, float _bystanderGravity, bool _sidesEnabled,
                                                 float _speedCap, int _trailThickness, uint8_t _fade,
                                                 float _mixingSpeed, float _mixingDistance, float _mixingRevertTime,
                                                 float _explosionAntigravity, float _explosionGravity,
                                                 float _explosionExTime, float _explosionInTime,
                                                 float _lightSourceGravity, float _colorHoleDelay,
                                                 float _colorHoleGravity, float _colorHoleRange,
                                                 float _colorHoleGravityRange, float _mixingEffectThickness,
                                                 float _colorHoleEffectThickness, float _colorHoleEffectPeriod,
                                                 float _proximityModifier)
=======
                                                 float _proximityRange, float _proximityModifier,
                                                 bool _sidesEnabled, float _speedCap, int _trailThickness,
                                                 uint8_t _fade, float _mixingSpeed, float _mixingDistance,
                                                 float _mixingRevertTime, float _explosionAntigravity,
                                                 float _explosionGravity, float _explosionExTime,
                                                 float _explosionInTime, float _lightSourceGravity,
                                                 float _colorHoleDelay, float _colorHoleGravity,
                                                 float _colorHoleRange, float _colorHoleGravityRange,
                                                 float _mixingEffectThickness, float _colorHoleEffectThickness,
                                                 float _colorHoleEffectPeriod, float _starAmount, float _starSpeed)
>>>>>>> Add configuration for star effect
        : _screenWidth(_screenWidth), _screenHeight(_screenHeight),
          _sendOutDelay(_sendOutDelay), _trailCap(_trailCap), _sendOutSpeed(_sendOutSpeed), _participantGravity(_participantGravity),
          _participantAntigravity(_participantAntigravity), _participantGravityRange(_participantGravityRange),
          _bystanderGravity(_bystanderGravity), _bystanderGravityDelay(_bystanderGravityDelay), _bystanderGravityRange(_bystanderGravityRange),
          _alternatingGravity(_alternatingGravity), _gravityPointDelay(_gravityPointDelay), _alternatingGravityRange(_alternatingGravityRange),
          _proximityRange(_proximityRange), _proximityModifier(_proximityModifier), _sidesEnabled(_sidesEnabled),
          _speedCap(_speedCap), _trailThickness(_trailThickness), _fade(_fade),
          _mixingSpeed(_mixingSpeed), _mixingDistance(_mixingDistance), _mixingRevertTime(_mixingRevertTime),
          _explosionAntigravity(_explosionAntigravity), _explosionGravity(_explosionGravity),
          _explosionExTime(_explosionExTime), _explosionInTime(_explosionInTime),
          _lightSourceGravity(_lightSourceGravity), _colorHoleDelay(_colorHoleDelay),
          _colorHoleGravity(_colorHoleGravity), _colorHoleRange(_colorHoleRange),
          _colorHoleGravityRange(_colorHoleGravityRange), _mixingEffectThickness(_mixingEffectThickness),
          _colorHoleEffectThickness(_colorHoleEffectThickness), _colorHoleEffectPeriod(_colorHoleEffectPeriod),
<<<<<<< a433a11f63b8a09e98546efa02c2aedebd785d20
          _participantGravityDistance(_participantGravityDistance) {
=======
          _starAmount(_starAmount), _starSpeed(_starSpeed) {
>>>>>>> Add configuration for star effect
    _cornerHues.push_back(_corner1Hue);
    _cornerHues.push_back(_corner2Hue);
    _cornerHues.push_back(_corner3Hue);
    _cornerHues.push_back(_corner4Hue);
}

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
    float participantGravity, participantAntiGravity, participantGravityDistance, bystanderGravity,
            bystanderGravityDelay, alternatingGravity, alternatingGravityDelay,
            proximityRange, proximityModifier, speedCap, mixingSpeed, mixingDistance, mixingRevertTime,
            explosionAntigravity, explosionGravity, explosionExTime, explosionInTime, meter,
            participantGravityRange, bystanderGravityRange, alternatingGravityRange;
    bool sidesEnabled;
    int fadeint;
    float trailThickness;
    float lightSourceGravity,colorHoleDelay,colorHoleGravity,colorHoleRange,colorHoleGravityRange;

    float mixingEffectThickness, colorHoleEffectThickness, colorHoleEffectPeriod;
    int starAmount;
    float starSpeed;

    fs["Resolution"] >> resolution;
    fs["Meter"] >> meter;
    fs["TopLeftHue"] >> topLeftRange;
    fs["TopRightHue"] >> topRightRange;
    fs["BottomRightHue"] >> bottomRightRange;
    fs["BottomLeftHue"] >> bottomLeftRange;
    fs["SendOutDelay"] >> sendOutDelay;
    fs["SendOutSpeed"] >> sendOutSpeed;
    fs["TrailCap"] >> trailCap;
    fs["ParticipantGravity"] >> participantGravity;
    fs["ParticipantAntiGravity"] >> participantAntiGravity;
    fs["ParticipantGravityDistance"] >> participantGravityDistance;
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
    fs["MixingSpeed"] >> mixingSpeed;
    fs["MixingDistance"] >> mixingDistance;
    fs["MixingRevertTime"] >> mixingRevertTime;
    fs["ExplosionAntigravity"] >> explosionAntigravity;
    fs["ExplosionGravity"] >> explosionGravity;
    fs["ExplosionExTime"] >> explosionExTime;
    fs["ExplosionInTime"] >> explosionInTime;
    fs["ParticipantGravityRange"] >> participantGravityRange;
    fs["BystanderGravityRange"] >> bystanderGravityRange;
    fs["AlternatingGravityRange"] >> alternatingGravityRange;
    fs["LightSourceGravity"] >> lightSourceGravity;
    fs["ColorHoleDelay"] >> colorHoleDelay;
    fs["ColorHoleGravity"] >> colorHoleGravity;
    fs["ColorHoleRange"] >> colorHoleRange;
    fs["ColorHoleGravityRange"] >> colorHoleGravityRange;
    fs["MixingEffectThickness"] >> mixingEffectThickness;
    fs["ColorHoleEffectThickness"] >> colorHoleEffectThickness;
    fs["ColorHoleEffectPeriod"] >> colorHoleEffectPeriod;
    fs["StarAmount"] >> starAmount;
    fs["StarSpeed"] >> starSpeed;

    uint8_t fade = static_cast<uint8_t>(fadeint > 255 ? 255 : fadeint);

    unsigned int w = static_cast<unsigned int>(resolution.width);
    unsigned int h = static_cast<unsigned int>(resolution.height);

    return LightTrailConfiguration(w, h, util::Range(topLeftRange.val[0], topLeftRange.val[1], true),
                                   util::Range(topRightRange.val[0], topRightRange.val[1], true),
                                   util::Range(bottomLeftRange.val[0], bottomLeftRange.val[1], true),
                                   util::Range(bottomRightRange.val[0], bottomRightRange.val[1], true), sendOutDelay,
                                   trailCap, util::Range(sendOutSpeed.val[0] * meter, sendOutSpeed.val[1] * meter),
                                   participantGravity * meter * meter, participantAntiGravity * meter * meter,
                                   participantGravityRange * meter, participantGravityDistance*meter, bystanderGravityDelay,
                                   bystanderGravityRange * meter, alternatingGravity * meter * meter,
                                   alternatingGravityDelay, alternatingGravityRange * meter, proximityRange * meter,
                                   bystanderGravity * meter * meter, sidesEnabled, speedCap * meter,
                                   (int) (trailThickness * meter), fade, mixingSpeed, mixingDistance * meter,
                                   mixingRevertTime, explosionAntigravity * meter * meter,
                                   explosionGravity * meter * meter, explosionExTime, explosionInTime,
                                   lightSourceGravity * meter * meter, colorHoleDelay, colorHoleGravity * meter * meter,
                                   colorHoleRange * meter, colorHoleGravityRange * meter, mixingEffectThickness,
<<<<<<< a433a11f63b8a09e98546efa02c2aedebd785d20
                                   colorHoleEffectThickness, colorHoleEffectPeriod, proximityModifier);
=======
                                   colorHoleEffectThickness, colorHoleEffectPeriod, starAmount,
                                   starSpeed*meter);
>>>>>>> Add configuration for star effect
}

int LightTrailConfiguration::trailThickness() const {
    return _trailThickness;
}

const std::vector<util::Range> &LightTrailConfiguration::cornerHues() const {
    return _cornerHues;
}

float LightTrailConfiguration::mixingSpeed() const {
    return _mixingSpeed;
}

float LightTrailConfiguration::mixingDistance() const {
    return _mixingDistance;
}

float LightTrailConfiguration::mixingRevertTime() const {
    return _mixingRevertTime;
}

float LightTrailConfiguration::explosionAntigravity() const {
    return _explosionAntigravity;
}

float LightTrailConfiguration::explosionGravity() const {
    return _explosionGravity;
}

float LightTrailConfiguration::explosionExTime() const {
    return _explosionExTime;
}

float LightTrailConfiguration::explosionInTime() const {
    return _explosionInTime;
}

float LightTrailConfiguration::participantGravityRange() const {
    return _participantGravityRange;
}

float LightTrailConfiguration::bystanderGravityRange() const {
    return _bystanderGravityRange;
}

float LightTrailConfiguration::alternatingGravityRange() const {
    return _alternatingGravityRange;
}

float LightTrailConfiguration::lightSourceGravity() const {
    return _lightSourceGravity;
}

float LightTrailConfiguration::colorHoleDelay() const {
    return _colorHoleDelay;
}

float LightTrailConfiguration::colorHoleGravity() const {
    return _colorHoleGravity;
}

float LightTrailConfiguration::colorHoleRange() const {
    return _colorHoleRange;
}

float LightTrailConfiguration::colorHoleGravityRange() const {
    return _colorHoleGravityRange;
}

float LightTrailConfiguration::mixingEffectThickness() const {
    return _mixingEffectThickness;
}

float LightTrailConfiguration::colorHoleEffectThickness() const {
    return _colorHoleEffectThickness;
}

float LightTrailConfiguration::colorHoleEffectPeriod() const {
    return _colorHoleEffectPeriod;
}

<<<<<<< a433a11f63b8a09e98546efa02c2aedebd785d20
float LightTrailConfiguration::participantGravityDistance() const {
    return _participantGravityDistance;
=======
float LightTrailConfiguration::starAmount() const {
    return _starAmount;
}

float LightTrailConfiguration::starSpeed() const {
    return _starSpeed;
>>>>>>> Add configuration for star effect
}