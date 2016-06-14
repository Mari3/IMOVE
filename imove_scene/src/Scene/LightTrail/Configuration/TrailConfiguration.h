//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_TRAILCONFIGURATION_H
#define IMOVE_TRAILCONFIGURATION_H

#include <vector>
#include <stdint.h>
#include "../../Util/Range.h"

struct LightSourceConfig {
    float sendOutDelay;
    int trailCap;
    util::Range sendOutSpeed;
};

struct TrailConfig {
    float speedCap;
    int thickness;
};

class TrailConfiguration {
private:
    // Light source hues
    std::vector<util::Range> _cornerHues;

    // Light sources
    LightSourceConfig _lightSourceConfig;

    // Sides
    bool _sidesEnabled;

    // Trail properties
    TrailConfig _trailConfig;

    // Display
    uint8_t _fade;
public:

    TrailConfiguration(const std::vector<util::Range> &_cornerHues, const LightSourceConfig &_lightSourceConfig,
                       bool _sidesEnabled, const TrailConfig &_trailConfig, uint8_t _fade);


    const std::vector<util::Range> & cornerHues() const;

    const LightSourceConfig & lightSource() const;

    bool sidesEnabled() const;

    const TrailConfig & trail() const;

    uint8_t fade() const;
};


#endif //IMOVE_TRAILCONFIGURATION_H
