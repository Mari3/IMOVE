//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_GRAVITYCONFGURATION_H
#define IMOVE_GRAVITYCONFGURATION_H

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
};


#endif //IMOVE_GRAVITYCONFGURATION_H
