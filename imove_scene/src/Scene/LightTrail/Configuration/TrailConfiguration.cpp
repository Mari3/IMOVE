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