//
// Created by Wouter Posdijk on 13/06/16.
//

#include "EffectConfiguration.h"

EffectConfiguration::EffectConfiguration(const MixingConfig &_mixingConfig, const ExplosionConfig &_explosionConfig,
                                         const ColorHoleConfig &_colorHoleConfig, const StarConfig &_starConfig,
                                         TrailEffectConfig _trailEffectConfig,
                                         SourceEffectConfig _sourceEffectConfig) : _mixingConfig(_mixingConfig),
                                                                                   _explosionConfig(_explosionConfig),
                                                                                   _colorHoleConfig(_colorHoleConfig),
                                                                                   _starConfig(_starConfig),
                                                                                   _trailEffectConfig(_trailEffectConfig),
                                                                                   _sourceEffectConfig(_sourceEffectConfig) { }

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

const TrailEffectConfig &EffectConfiguration::trail() const {
    return _trailEffectConfig;
}

const EffectConfiguration EffectConfiguration::readFromFile(cv::FileStorage fs, float meter) {
    return EffectConfiguration(MixingConfig(fs, meter), ExplosionConfig(fs, meter), ColorHoleConfig(fs, meter),
                               StarConfig(fs, meter), TrailEffectConfig(fs, meter),
                               SourceEffectConfig(fs,meter));
}


const SourceEffectConfig &EffectConfiguration::source() const {
    return _sourceEffectConfig;
}