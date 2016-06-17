//
// Created by Wouter Posdijk on 24/05/16.
//

#include <opencv2/opencv.hpp>
#include "LightTrailSceneConfiguration.h"

LightTrailSceneConfiguration LightTrailSceneConfiguration::readFromFile(char *fileName) {
    cv::FileStorage fs;
    fs.open(fileName, cv::FileStorage::READ);

    cv::Size resolution;
    float meter;

    fs["Resolution"] >> resolution;
    fs["Meter"] >> meter;

    unsigned int w = static_cast<unsigned int>(resolution.width);
    unsigned int h = static_cast<unsigned int>(resolution.height);

    return LightTrailSceneConfiguration(w, h,
                                        TrailConfiguration::readFromFile(fs,meter),
                                        GravityConfiguration::readFromFile(fs,meter),
                                        EffectConfiguration::readFromFile(fs,meter)
    );
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