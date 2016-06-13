//
// Created by Wouter Posdijk on 13/06/16.
//

#include "EffectConfiguration.h"

EffectConfiguration::EffectConfiguration(const MixingConfig &_mixingConfig, const ExplosionConfig &_explosionConfig,
                                         const ColorHoleConfig &_colorHoleConfig, const StarConfig &_starConfig,
                                         float _standingStillFadeTime) : _mixingConfig(_mixingConfig),
                                                                         _explosionConfig(_explosionConfig),
                                                                         _colorHoleConfig(_colorHoleConfig), _starConfig(_starConfig),
                                                                         _standingStillFadeTime(_standingStillFadeTime) { }

const MixingConfig &EffectConfiguration::mixing() const {
    return _mixingConfig;
}

const ExplosionConfig &EffectConfiguration::explosion() const {
    return _explosionConfig;
}

const ColorHoleConfig &EffectConfiguration::colorHole() const {
    return _colorHoleConfig;
}

const StarConfig &EffectConfiguration::star() const {
    return _starConfig;
}

float EffectConfiguration::standingStillFadeTime() const {
    return _standingStillFadeTime;
}