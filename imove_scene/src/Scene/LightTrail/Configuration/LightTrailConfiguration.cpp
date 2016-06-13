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
    return _lightSourceConfig.sendOutDelay;
}

int LightTrailConfiguration::trailCap() const {
    return _lightSourceConfig.trailCap;
}

float LightTrailConfiguration::participantGravity() const {
    return _participantGravityConfig.gravity;
}

float LightTrailConfiguration::participantAntigravity() const {
    return _participantGravityConfig.antigravity;
}

float LightTrailConfiguration::bystanderGravity() const {
    return _bystanderGravityConfig.gravity;
}

float LightTrailConfiguration::alternatingGravity() const {
    return _alternatingGravityConfig.gravity;
}

float LightTrailConfiguration::gravityPointDelay() const {
    return _alternatingGravityConfig.delay;
}

float LightTrailConfiguration::proximityRange() const {
    return _proximityConfig.range;
}

float LightTrailConfiguration::proximityModifier() const {
    return _proximityConfig.modifier;
}

bool LightTrailConfiguration::sidesEnabled() const {
    return _sidesEnabled;
}

float LightTrailConfiguration::speedCap() const {
    return _trailConfig.speedCap;
}

uint8_t LightTrailConfiguration::fade() const {
    return _fade;
}



float LightTrailConfiguration::bystanderGravityDelay() const {
    return _bystanderGravityConfig.delay;
}

const util::Range &LightTrailConfiguration::sendOutSpeed() const {
    return _lightSourceConfig.sendOutSpeed;
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
    // Screen size
    std::vector<util::Range> cornerHues;
    LightSourceConfig lightSourceConfig;
    ParticipantGravityConfig participantGravityConfig;
    DelayGravityConfig bystanderGravityConfig;
    DelayGravityConfig alternatingGravityConfig;
    ProximityConfig proximityConfig;
    bool sidesEnabled;
    TrailConfig trailConfig;
    MixingConfig mixingConfig;
    ExplosionConfig explosionConfig;
    GravityConfig lightSourceGravityConfig;
    ColorHoleConfig colorHoleConfig;
    StarConfig starConfig;

    float meter;
    int fadeint;

    fs["Resolution"] >> resolution;
    fs["Meter"] >> meter;
    fs["TopLeftHue"] >> topLeftRange;
    fs["TopRightHue"] >> topRightRange;
    fs["BottomRightHue"] >> bottomRightRange;
    fs["BottomLeftHue"] >> bottomLeftRange;
    cornerHues.push_back(util::Range(topLeftRange.val[0],topLeftRange.val[1],true));
    cornerHues.push_back(util::Range(topRightRange.val[0],topRightRange.val[1],true));
    cornerHues.push_back(util::Range(bottomRightRange.val[0],bottomRightRange.val[1],true));
    cornerHues.push_back(util::Range(bottomLeftRange.val[0],bottomLeftRange.val[1],true));

    fs["SendOutDelay"] >> lightSourceConfig.sendOutDelay;
    fs["SendOutSpeed"] >> sendOutSpeed;
    lightSourceConfig.sendOutSpeed = util::Range(sendOutSpeed.val[0]*meter,sendOutSpeed.val[1]*meter);

    fs["TrailCap"] >> lightSourceConfig.trailCap;

    fs["ParticipantGravity"] >> participantGravityConfig.gravity;
    participantGravityConfig.gravity *= meter*meter;

    fs["ParticipantAntiGravity"] >> participantGravityConfig.antigravity;
    participantGravityConfig.antigravity *= meter*meter;

    fs["BystanderGravity"] >> bystanderGravityConfig.gravity;
    bystanderGravityConfig.gravity *= meter*meter;

    fs["BystanderGravityDelay"] >> bystanderGravityConfig.delay;
    fs["AlternatingGravity"] >> alternatingGravityConfig.gravity;
    alternatingGravityConfig.gravity *= meter*meter;

    fs["AlternatingGravityDelay"] >> alternatingGravityConfig.delay;
    fs["ProximityRange"] >> proximityConfig.range;
    proximityConfig.range *= meter;
    fs["ProximityModifier"] >> proximityConfig.modifier;
    fs["SidesEnabled"] >> sidesEnabled;
    fs["SpeedCap"] >> trailConfig.speedCap;
    trailConfig.speedCap *= meter;
    fs["Fade"] >> fadeint;

    float thickness;
    fs["TrailThickness"] >> thickness;
    trailConfig.thickness = static_cast<int>(thickness*meter);

    fs["MixingSpeed"] >> mixingConfig.speed;
    fs["MixingDistance"] >> mixingConfig.distance;
    mixingConfig.distance*=meter;
    fs["MixingRevertTime"] >> mixingConfig.revertTime;
    fs["ExplosionAntigravity"] >> explosionConfig.antigravity;
    explosionConfig.antigravity *= meter*meter;
    fs["ExplosionGravity"] >> explosionConfig.gravity;
    explosionConfig.gravity *= meter*meter;
    fs["ExplosionExTime"] >> explosionConfig.exTime;
    fs["ExplosionInTime"] >> explosionConfig.inTime;
    fs["ParticipantGravityRange"] >> participantGravityConfig.range;
    participantGravityConfig.range *= meter;
    fs["BystanderGravityRange"] >> bystanderGravityConfig.range;
    bystanderGravityConfig.range *= meter;
    fs["AlternatingGravityRange"] >> alternatingGravityConfig.range;
    alternatingGravityConfig.range *= meter;
    fs["LightSourceGravity"] >> lightSourceGravityConfig.gravity;
    lightSourceGravityConfig.gravity *= meter*meter;
    lightSourceGravityConfig.range = -1;
    fs["ColorHoleDelay"] >> colorHoleConfig.delay;
    fs["ColorHoleGravity"] >> colorHoleConfig.gravity;
    colorHoleConfig.gravity *= meter*meter;
    fs["ColorHoleRange"] >> colorHoleConfig.consumeRange;
    colorHoleConfig.consumeRange *= meter;
    fs["ColorHoleGravityRange"] >> colorHoleConfig.range;
    colorHoleConfig.range *= meter;

    fs["StarAmount"] >> starConfig.amount;
    fs["StarSpeed"] >> starConfig.speed;
    starConfig.speed *= meter;

    fs["ColorHoleEffectThickness"] >> colorHoleConfig.thickness;
    fs["ColorHoleEffectPeriod"] >> colorHoleConfig.period;

    fs["MixingEffectThickness"] >> mixingConfig.thickness;
    mixingConfig.thickness *= meter;

    float standingStillFadeTime;
    fs["StandingStillFadeTime"] >> standingStillFadeTime;

    uint8_t fade = static_cast<uint8_t>(fadeint > 255 ? 255 : fadeint);

    unsigned int w = static_cast<unsigned int>(resolution.width);
    unsigned int h = static_cast<unsigned int>(resolution.height);

    return LightTrailConfiguration(w, h, cornerHues, lightSourceConfig, participantGravityConfig,
                                   bystanderGravityConfig, alternatingGravityConfig,
                                   proximityConfig, sidesEnabled, trailConfig, fade, mixingConfig, explosionConfig,
                                   lightSourceGravityConfig,
                                   colorHoleConfig, starConfig, standingStillFadeTime);
}

int LightTrailConfiguration::trailThickness() const {
    return _trailConfig.thickness;
}

const std::vector<util::Range> &LightTrailConfiguration::cornerHues() const {
    return _cornerHues;
}

float LightTrailConfiguration::mixingSpeed() const {
    return _mixingConfig.speed;
}

float LightTrailConfiguration::mixingDistance() const {
    return _mixingConfig.distance;
}

float LightTrailConfiguration::mixingRevertTime() const {
    return _mixingConfig.revertTime;
}

float LightTrailConfiguration::explosionAntigravity() const {
    return _explosionConfig.antigravity;
}

float LightTrailConfiguration::explosionGravity() const {
    return _explosionConfig.gravity;
}

float LightTrailConfiguration::explosionExTime() const {
    return _explosionConfig.exTime;
}

float LightTrailConfiguration::explosionInTime() const {
    return _explosionConfig.inTime;
}

float LightTrailConfiguration::participantGravityRange() const {
    return _participantGravityConfig.range;
}

float LightTrailConfiguration::bystanderGravityRange() const {
    return _bystanderGravityConfig.range;
}

float LightTrailConfiguration::alternatingGravityRange() const {
    return _alternatingGravityConfig.range;
}

float LightTrailConfiguration::lightSourceGravity() const {
    return _lightSourceGravityConfig.gravity;
}

float LightTrailConfiguration::colorHoleDelay() const {
    return _colorHoleConfig.delay;
}

float LightTrailConfiguration::colorHoleGravity() const {
    return _colorHoleConfig.gravity;
}

float LightTrailConfiguration::colorHoleRange() const {
    return _colorHoleConfig.consumeRange;
}

float LightTrailConfiguration::colorHoleGravityRange() const {
    return _colorHoleConfig.range;
}

int LightTrailConfiguration::starAmount() const {
    return _starConfig.amount;
}

float LightTrailConfiguration::starSpeed() const {
    return _starConfig.speed;
}

float LightTrailConfiguration::participantGravityDistance() const {
    return _participantGravityConfig.distance;
}

LightTrailConfiguration::LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight,
                                                 const std::vector<util::Range> &_cornerHues,
                                                 const LightSourceConfig &_lightSourceConfig,
                                                 const ParticipantGravityConfig &_participantGravityConfig,
                                                 const DelayGravityConfig &_bystanderGravityConfig,
                                                 const DelayGravityConfig &_alternatingGravityConfig,
                                                 const ProximityConfig &_proximityConfig, bool _sidesEnabled,
                                                 const TrailConfig &_trailConfig, uint8_t _fade,
                                                 const MixingConfig &_mixingConfig,
                                                 const ExplosionConfig &_explosionConfig,
                                                 const GravityConfig &_lightSourceGravityConfig,
                                                 const ColorHoleConfig &_colorHoleConfig,
                                                 const StarConfig &_starConfig, float _standingStillFadeTime)
        : _screenWidth(_screenWidth),
          _screenHeight(_screenHeight),
          _cornerHues(_cornerHues),
          _lightSourceConfig(_lightSourceConfig),
          _participantGravityConfig(
                                                                                                    _participantGravityConfig),
          _bystanderGravityConfig(_bystanderGravityConfig),
          _alternatingGravityConfig(
                                                                                                    _alternatingGravityConfig),
          _proximityConfig(_proximityConfig),
          _sidesEnabled(_sidesEnabled),
          _trailConfig(_trailConfig), _fade(_fade),
          _mixingConfig(_mixingConfig),
          _explosionConfig(_explosionConfig),
          _lightSourceGravityConfig(
                                                                                                    _lightSourceGravityConfig),
          _colorHoleConfig(_colorHoleConfig), _starConfig(_starConfig), _standingStillFadeTime(_standingStillFadeTime) { }

float LightTrailConfiguration::colorHoleEffectThickness() const {
    return _colorHoleConfig.thickness;
}

float LightTrailConfiguration::colorHoleEffectPeriod() const {
    return _colorHoleConfig.period;
}

float LightTrailConfiguration::mixingEffectThickness() const {
    return _mixingConfig.thickness;
}


float LightTrailConfiguration::standingStillFadeTime() const {
    return _standingStillFadeTime;
}