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
    float speedCap, maxLength;
    int thickness;
};

struct DrawConfig {
    uint8_t fade;
    bool inverted;
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
    DrawConfig _drawConfig;
public:

    TrailConfiguration(const std::vector<util::Range> &_cornerHues, const LightSourceConfig &_lightSourceConfig,
                       bool _sidesEnabled, const TrailConfig &_trailConfig, const DrawConfig &_drawConfig);


    const std::vector<util::Range> & cornerHues() const;

    const LightSourceConfig & lightSource() const;

    bool sidesEnabled() const;

    const TrailConfig & trail() const;

    const DrawConfig & draw() const;
};


#endif //IMOVE_TRAILCONFIGURATION_H
