//
// Created by Wouter Posdijk on 12/05/16.
//

#ifndef IMOVE_RANGE_H
#define IMOVE_RANGE_H


class Range {
private:
    float start, end, lowerBound, upperBound;
    bool bounds;
    void fixBounds();
public:
    Range(float start, float end, bool bounds=false, float lowerBound=0.f, float upperBound=1.f);
    void operator+=(const float& f);
    float drawRandom();
};


#endif //IMOVE_RANGE_H
