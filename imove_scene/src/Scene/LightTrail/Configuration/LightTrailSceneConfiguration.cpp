//
// Created by Wouter Posdijk on 24/05/16.
//

#include <opencv2/opencv.hpp>
#include "LightTrailSceneConfiguration.h"

LightTrailSceneConfiguration LightTrailSceneConfiguration::readFromFile(char *fileName) {
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

    fs["TrailMaxLength"] >> trailConfig.maxLength;

    float standingStillFadeTime;
    fs["StandingStillFadeTime"] >> standingStillFadeTime;

    uint8_t fade = static_cast<uint8_t>(fadeint > 255 ? 255 : fadeint);

    unsigned int w = static_cast<unsigned int>(resolution.width);
    unsigned int h = static_cast<unsigned int>(resolution.height);

    TrailConfiguration trailConfiguration(cornerHues,lightSourceConfig,sidesEnabled,trailConfig,fade);
    EffectConfiguration effectConfiguration(mixingConfig,explosionConfig,colorHoleConfig,starConfig,standingStillFadeTime);
    GravityConfiguration gravityConfiguration(lightSourceGravityConfig,participantGravityConfig,
                                              bystanderGravityConfig,alternatingGravityConfig,
                                              proximityConfig
    );

    return LightTrailSceneConfiguration(w, h, trailConfiguration, gravityConfiguration, effectConfiguration);
}

LightTrailSceneConfiguration::LightTrailSceneConfiguration(unsigned int _screenWidth, unsigned int _screenHeight,
                                                           const TrailConfiguration &_trailConfiguration,
                                                           const GravityConfiguration &_gravityConfiguration,
                                                           const EffectConfiguration &_effectConfiguration)
        : _screenWidth(_screenWidth),
          _screenHeight(_screenHeight),
          _trailConfiguration(
                  _trailConfiguration),
          _gravityConfiguration(
                  _gravityConfiguration),
          _effectConfiguration(
                  _effectConfiguration) { }

unsigned int LightTrailSceneConfiguration::screenWidth() const {
    return _screenWidth;
}

unsigned int LightTrailSceneConfiguration::screenHeight() const {
    return _screenHeight;
}

const TrailConfiguration &LightTrailSceneConfiguration::trail() const {
    return _trailConfiguration;
}

const GravityConfiguration &LightTrailSceneConfiguration::gravity() const {
    return _gravityConfiguration;
}

const EffectConfiguration &LightTrailSceneConfiguration::effect() const {
    return _effectConfiguration;
}