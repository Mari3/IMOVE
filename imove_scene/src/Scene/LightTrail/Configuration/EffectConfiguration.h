//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_EFFECTCONFIGURATION_H
#define IMOVE_EFFECTCONFIGURATION_H

#include <opencv2/core/persistence.hpp>

struct ColorHoleConfig {
    float gravity, range, delay, consumeRange, thickness, period, destructionRange;
    ColorHoleConfig(){}
    ColorHoleConfig(cv::FileStorage fs, float meter){
        fs["ColorHoleDelay"] >> delay;
        fs["ColorHoleGravity"] >> gravity;
        fs["ColorHoleRange"] >> consumeRange;
        fs["ColorHoleGravityRange"] >> range;
        fs["ColorHoleDestructionRange"] >> destructionRange;
        fs["ColorHoleEffectThickness"] >> thickness;
        fs["ColorHoleEffectPeriod"] >> period;

        gravity *= meter*meter;
        consumeRange *= meter;
        range *= meter;
        destructionRange *= meter;
    }
};

struct MixingConfig {
    float speed, distance, revertTime, thickness, trailRange;
    MixingConfig(){}
    MixingConfig(cv::FileStorage fs, float meter){
        fs["MixingSpeed"] >> speed;
        fs["MixingDistance"] >> distance;
        fs["MixingRevertTime"] >> revertTime;
        fs["MixingEffectThickness"] >> thickness;
        fs["MixingTrailRange"] >> trailRange;

        distance *= meter;
        thickness *= meter;
        trailRange *= meter;
    }
};

struct ExplosionConfig {
    float gravity, antigravity, inTime, exTime;
    ExplosionConfig(){}
    ExplosionConfig(cv::FileStorage fs, float meter){
        fs["ExplosionAntigravity"] >> antigravity;
        fs["ExplosionGravity"] >> gravity;
        fs["ExplosionExTime"] >> exTime;
        fs["ExplosionInTime"] >> inTime;

        antigravity *= meter*meter;
        gravity *= meter*meter;
    }
};

struct StarConfig {
    int amount;
    float speed;
    StarConfig(){}
    StarConfig(cv::FileStorage fs, float meter){
        fs["StarAmount"] >> amount;
        fs["StarSpeed"] >> speed;

        speed *= meter;
    }
};

struct TrailEffectConfig {
    int bystanderInitAmount, participantInitAmount;
    float initRange, standingStillFadeTime;
    TrailEffectConfig(){}
    TrailEffectConfig(cv::FileStorage fs, float meter){
        fs["InitiateTrailRange"] >> initRange;
        fs["BystanderInitiateTrails"] >> bystanderInitAmount;
        fs["ParticipantInitiateTrails"] >> participantInitAmount;
        fs["StandingStillFadeTime"] >> standingStillFadeTime;

        initRange *= meter;
    }
};

class EffectConfiguration {
private:
    // Mixing
    MixingConfig _mixingConfig;

    // Explosion
    ExplosionConfig _explosionConfig;

    ColorHoleConfig _colorHoleConfig;

    StarConfig _starConfig;

    TrailEffectConfig _trailEffectConfig;
public:

    EffectConfiguration(const MixingConfig &_mixingConfig, const ExplosionConfig &_explosionConfig,
                            const ColorHoleConfig &_colorHoleConfig, const StarConfig &_starConfig,
                            TrailEffectConfig _trailEffectConfig);


    const MixingConfig & mixing() const;

    const ExplosionConfig & explosion() const;

    const ColorHoleConfig & colorHole() const;

    const StarConfig & star() const;

    const TrailEffectConfig & trail() const;

    static const EffectConfiguration readFromFile(cv::FileStorage fs, float meter);
};


#endif //IMOVE_EFFECTCONFIGURATION_H
