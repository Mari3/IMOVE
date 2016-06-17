//
// Created by Wouter Posdijk on 13/06/16.
//

#include "TrailConfiguration.h"

TrailConfiguration::TrailConfiguration(const std::vector<util::Range> &_cornerHues, const LightSourceConfig &_lightSourceConfig,
                                       bool _sidesEnabled, const TrailConfig &_trailConfig, const DrawConfig &_drawConfig)
        : _cornerHues(_cornerHues),
          _lightSourceConfig(
                  _lightSourceConfig),
          _sidesEnabled(
                  _sidesEnabled),
          _trailConfig(_trailConfig),
          _drawConfig(_drawConfig) { }

const std::vector<util::Range> &TrailConfiguration::cornerHues() const {
    return _cornerHues;
}

const LightSourceConfig &TrailConfiguration::lightSource() const {
    return _lightSourceConfig;
}

bool TrailConfiguration::sidesEnabled() const {
    return _sidesEnabled;
}

const TrailConfig &TrailConfiguration::trail() const {
    return _trailConfig;
}

const DrawConfig &TrailConfiguration::draw() const {
    return _drawConfig;
}

const TrailConfiguration TrailConfiguration::readFromFile(cv::FileStorage fs, float meter) {
    // Read corner hues
    cv::Vec2f topLeftRange;
    cv::Vec2f topRightRange;
    cv::Vec2f bottomRightRange;
    cv::Vec2f bottomLeftRange;
    fs["TopLeftHue"] >> topLeftRange;
    fs["TopRightHue"] >> topRightRange;
    fs["BottomRightHue"] >> bottomRightRange;
    fs["BottomLeftHue"] >> bottomLeftRange;
    std::vector<util::Range> cornerHues;
    cornerHues.push_back(util::Range(topLeftRange.val[0],topLeftRange.val[1],true));
    cornerHues.push_back(util::Range(topRightRange.val[0],topRightRange.val[1],true));
    cornerHues.push_back(util::Range(bottomRightRange.val[0],bottomRightRange.val[1],true));
    cornerHues.push_back(util::Range(bottomLeftRange.val[0],bottomLeftRange.val[1],true));

    // Read sides enabled
    bool sidesEnabled;
    fs["SidesEnabled"] >> sidesEnabled;

    return TrailConfiguration(cornerHues,
                              LightSourceConfig(fs,meter),
                              sidesEnabled,
                              TrailConfig(fs,meter),
                              DrawConfig(fs,meter)
    );
}

