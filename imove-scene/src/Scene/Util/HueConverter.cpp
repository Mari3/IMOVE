//
// Created by Wouter Posdijk on 12/05/16.
//

#include <math.h>
#include <cstdint>
#include "HueConverter.h"

namespace HueConverter {
    sf::Color ToColor(float hue) {
        float x = (1 - fabsf(fmodf(hue / 60.f, 2.f) - 1));
        uint8_t xval = (uint8_t) (255 * x);

        if (hue < 60)
            return sf::Color(255, xval, 0);
        if (hue < 120)
            return sf::Color(xval, 255, 0);
        if (hue < 180)
            return sf::Color(0, 255, xval);
        if (hue < 240)
            return sf::Color(0, xval, 255);
        if (hue < 300)
            return sf::Color(xval, 0, 255);

        return sf::Color(255, 0, xval);
    }
} // namespace HueConverter
