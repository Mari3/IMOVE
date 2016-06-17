//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_GRAVITYCONFGURATION_H
#define IMOVE_GRAVITYCONFGURATION_H

#include <opencv2/core/persistence.hpp>

struct GravityConfig {
    float gravity, range;
    GravityConfig(){}
    GravityConfig(cv::FileStorage fs, float meter, cv::String prefix){
        fs[prefix + "Gravity"] >> gravity;
        fs[prefix + "GravityRange"] >> range;

        gravity *= meter*meter;
        range *= meter;
    }
};

struct ParticipantGravityConfig : public GravityConfig {
    float antigravity, distance, movedThreshold, sideThreshold;
    ParticipantGravityConfig(){}
    ParticipantGravityConfig(cv::FileStorage fs, float meter)
    : GravityConfig(fs,meter,"Participant")
    {
        fs["ParticipantAntiGravity"] >> antigravity;
        fs["ParticipantGravityDistance"] >> distance;
        fs["ParticipantMovedThreshold"] >> movedThreshold;
        fs["ParticipantSideThreshold"] >> sideThreshold;

        antigravity *= meter*meter;
        distance *= meter;
        movedThreshold *= meter;
        sideThreshold *= meter;
    }
};

struct DelayGravityConfig : public GravityConfig {
    float delay;
    DelayGravityConfig(){}
    DelayGravityConfig(cv::FileStorage fs, float meter, cv::String prefix)
    : GravityConfig(fs,meter,prefix)
    {
        fs[prefix + "GravityDelay"] >> delay;
    }
};

struct ProximityConfig {
    float range, modifier;
    ProximityConfig(){}
    ProximityConfig(cv::FileStorage fs, float meter){
        fs["ProximityRange"] >> range;
        fs["ProximityModifier"] >> modifier;

        range *= meter;
    }
};

class GravityConfiguration {
private:
    GravityConfig _lightSourceGravityConfig;
    ParticipantGravityConfig _participantGravityConfig;
    DelayGravityConfig _bystanderGravityConfig;
    DelayGravityConfig _alternatingGravityConfig;
    ProximityConfig _proximityConfig;
public:
    GravityConfiguration(const GravityConfig &_lightSourceGravityConfig,
                        const ParticipantGravityConfig &_participantGravityConfig,
                        const DelayGravityConfig &_bystanderGravityConfig,
                        const DelayGravityConfig &_alternatingGravityConfig, const ProximityConfig &_proximityConfig);

    const GravityConfig & lightSource() const;

    const ParticipantGravityConfig & participant() const;

    const DelayGravityConfig & bystander() const;

    const DelayGravityConfig & alternating() const;

    const ProximityConfig & proximity() const;

    static const GravityConfiguration readFromFile(cv::FileStorage fs, float meter);
};


#endif //IMOVE_GRAVITYCONFGURATION_H
