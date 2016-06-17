//
// Created by Wouter Posdijk on 13/06/16.
//

#include "GravityConfiguration.h"

GravityConfiguration::GravityConfiguration(const GravityConfig &_lightSourceGravityConfig,
                                         const ParticipantGravityConfig &_participantGravityConfig,
                                         const DelayGravityConfig &_bystanderGravityConfig,
                                         const DelayGravityConfig &_alternatingGravityConfig, const ProximityConfig &_proximityConfig)
        : _lightSourceGravityConfig(_lightSourceGravityConfig),
          _participantGravityConfig(_participantGravityConfig), _bystanderGravityConfig(_bystanderGravityConfig),
          _alternatingGravityConfig(_alternatingGravityConfig), _proximityConfig(_proximityConfig) { }

const GravityConfig &GravityConfiguration::lightSource() const {
    return _lightSourceGravityConfig;
}

const ParticipantGravityConfig &GravityConfiguration::participant() const {
    return _participantGravityConfig;
}

const DelayGravityConfig &GravityConfiguration::bystander() const {
    return _bystanderGravityConfig;
}

const DelayGravityConfig &GravityConfiguration::alternating() const {
    return _alternatingGravityConfig;
}

const ProximityConfig &GravityConfiguration::proximity() const {
    return _proximityConfig;
}

const GravityConfiguration GravityConfiguration::readFromFile(cv::FileStorage fs, float meter) {
    return GravityConfiguration(GravityConfig(fs,meter,"LightSource"),
                                ParticipantGravityConfig(fs,meter),
                                DelayGravityConfig(fs,meter,"Bystander"),
                                DelayGravityConfig(fs,meter,"Alternating"),
                                ProximityConfig(fs,meter)
    );
}

