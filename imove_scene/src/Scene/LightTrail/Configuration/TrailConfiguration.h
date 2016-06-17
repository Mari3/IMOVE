//
// Created by Wouter Posdijk on 13/06/16.
//

#ifndef IMOVE_TRAILCONFIGURATION_H
#define IMOVE_TRAILCONFIGURATION_H

#include <vector>
#include <stdint.h>
#include <opencv2/core/persistence.hpp>
#include "../../Util/Range.h"

struct LightSourceConfig {
    float sendOutDelay;
    int trailCap;
    util::Range sendOutSpeed;
    LightSourceConfig(){}
    LightSourceConfig(cv::FileStorage fs, float meter){
        fs["SendOutDelay"] >> sendOutDelay;

        cv::Vec2f sos;
        fs["SendOutSpeed"] >> sos;
        sendOutSpeed = util::Range(sos.val[0]*meter,sos.val[1]*meter);

        fs["TrailCap"] >> trailCap;
    }
};

struct TrailConfig {
    float speedCap, maxLength;
    int thickness;
    TrailConfig(){}
    TrailConfig(cv::FileStorage fs, float meter){
        fs["SpeedCap"] >> speedCap;
        speedCap *= meter;

        fs["TrailMaxLength"] >> maxLength;

        float _thickness;
        fs["TrailThickness"] >> _thickness;
        thickness = static_cast<int>(_thickness*meter);
    }
};

struct DrawConfig {
    uint8_t fade;
    bool inverted;
    DrawConfig(){}
    DrawConfig(cv::FileStorage fs, float meter){
        fs["Inverted"] >> inverted;

        int fadeint;
        fs["Fade"] >> fadeint;
        fade = static_cast<uint8_t>(fadeint > 255 ? 255 : fadeint);
    }
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

    static const TrailConfiguration readFromFile(cv::FileStorage fs, float meter);
};


#endif //IMOVE_TRAILCONFIGURATION_H
