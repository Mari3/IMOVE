//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_EFFECTCONFIGURATION_H
#define IMOVE_EFFECTCONFIGURATION_H

struct ColorHoleConfig {
    float gravity, range, delay, consumeRange, thickness, period, destructionRange;
};

struct MixingConfig {
    float speed, distance, revertTime, thickness;
};

struct ExplosionConfig {
    float gravity, antigravity, inTime, exTime;
};

struct StarConfig {
    int amount;
    float speed;
};

class EffectConfiguration {
private:
    // Mixing
    MixingConfig _mixingConfig;

    // Explosion
    ExplosionConfig _explosionConfig;

    ColorHoleConfig _colorHoleConfig;

    StarConfig _starConfig;

    float _standingStillFadeTime;
public:

    EffectConfiguration(const MixingConfig &_mixingConfig, const ExplosionConfig &_explosionConfig,
                        const ColorHoleConfig &_colorHoleConfig, const StarConfig &_starConfig,
                        float _standingStillFadeTime);


    const MixingConfig & mixing() const;

    const ExplosionConfig & explosion() const;

    const ColorHoleConfig & colorHole() const;

    const StarConfig & star() const;

    float standingStillFadeTime() const;
};


#endif //IMOVE_EFFECTCONFIGURATION_H
