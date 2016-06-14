//
// Created by Wouter Posdijk on 12/05/16.
//

#include <math.h>
#include <cstdint>
#include "HueConverter.h"

namespace HueConverter {
    sf::Color ToColor(float hue) {

        float l = .5f;
        if(hue < 90 && hue > 30) {
            l = .5f * (1 - (hue - 30) / 120.f);
        }else if(hue < 150 && hue > 90){
            l = .5f * (1 - (hue - 90) / 120.f);
        }else if(hue < 210 && hue > 150){
            l = .5f*(1 - (hue-150)/120.f);
        }

        float c = 1 - fabsf(2*l-1);
        float x = c*(1 - fabsf(fmodf(hue / 60.f, 2.f) - 1));
        float m = l - c/2;

        uint8_t xval = (uint8_t) (255 * (x + m));
        uint8_t cval = (uint8_t) (255 * (c + m));
        uint8_t mval = (uint8_t) (255 * m);

        if (hue < 60)
            return sf::Color(cval, xval, mval);
        if (hue < 120)
            return sf::Color(xval, cval, mval);
        if (hue < 180)
            return sf::Color(mval, cval, xval);
        if (hue < 240)
            return sf::Color(mval, xval, cval);
        if (hue < 300)
            return sf::Color(xval, mval, cval);

        return sf::Color(cval, mval, xval);
    }
} // namespace HueConverter
