//
// Created by Wouter Posdijk on 24/05/16.
//

#ifndef IMOVE_LIGHTTRAILCONFIGURATION_H
#define IMOVE_LIGHTTRAILCONFIGURATION_H

#include <cstdint>
#include <string>
#include <vector>
#include "../../Util/Range.h"

struct LightSourceConfig {
    float sendOutDelay;
    int trailCap;
    util::Range sendOutSpeed;
};

struct GravityConfig {
    float gravity, range;
};

struct ParticipantGravityConfig : public GravityConfig {
    float antigravity, distance;
};

struct DelayGravityConfig : public GravityConfig {
    float delay;
};

struct ProximityConfig {
    float range, modifier;
};

struct TrailConfig {
    float speedCap;
    int thickness;
};

struct MixingConfig {
    float speed, distance, revertTime, thickness;
};

struct ExplosionConfig {
    float gravity, antigravity, inTime, exTime;
};

struct ColorHoleConfig : GravityConfig {
    float delay, consumeRange, thickness, period;
};

struct StarConfig {
    int amount;
    float speed;
};

class LightTrailConfiguration {
private:
    // Screen size
    unsigned int _screenWidth, _screenHeight;

    // Light source hues
    std::vector<util::Range> _cornerHues;

    // Light sources
    LightSourceConfig _lightSourceConfig;

    // Player gravitation
    ParticipantGravityConfig _participantGravityConfig;
    DelayGravityConfig _bystanderGravityConfig;

    // Other gravitation
    DelayGravityConfig _alternatingGravityConfig;

    // Orbiting
    ProximityConfig _proximityConfig;

    // Sides
    bool _sidesEnabled;

    // Trail properties
    TrailConfig _trailConfig;

    // Display
    uint8_t _fade;

    // Mixing
    MixingConfig _mixingConfig;

    // Explosion
    ExplosionConfig _explosionConfig;

    GravityConfig _lightSourceGravityConfig;

    ColorHoleConfig _colorHoleConfig;

    StarConfig _starConfig;

    float _standingStillFadeTime;

public:


    LightTrailConfiguration(unsigned int _screenWidth, unsigned int _screenHeight,
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
                                const StarConfig &_starConfig, float _standingStillFadeTime);

    static LightTrailConfiguration readFromFile(char* fileName);

    unsigned int screenWidth() const;

    unsigned int screenHeight() const;

    const std::vector<util::Range> & cornerHues() const;

    float sendOutDelay() const;

    int trailCap() const;

    float participantGravity() const;

    float participantAntigravity() const;

    float bystanderGravity() const;

    float bystanderGravityDelay() const;

    float alternatingGravity() const;

    float gravityPointDelay() const;

    float proximityRange() const;

    float proximityModifier() const;

    bool sidesEnabled() const;

    float speedCap() const;

    uint8_t fade() const;

    const util::Range & sendOutSpeed() const;

    int trailThickness() const;

    float mixingSpeed() const;

    float mixingDistance() const;

    float mixingRevertTime() const;

    float explosionAntigravity() const;

    float explosionGravity() const;

    float explosionExTime() const;

    float explosionInTime() const;

    float participantGravityRange() const;

    float bystanderGravityRange() const;

    float alternatingGravityRange() const;


    float lightSourceGravity() const;

    float colorHoleDelay() const;

    float colorHoleGravity() const;

    float colorHoleRange() const;


    float colorHoleGravityRange() const;

    float participantGravityDistance() const;

    float colorHoleEffectThickness() const;

    float colorHoleEffectPeriod() const;

    float mixingEffectThickness() const;

    int starAmount() const;

    float starSpeed() const;


    float standingStillFadeTime() const;
};


#endif //IMOVE_LIGHTTRAILCONFIGURATION_H
