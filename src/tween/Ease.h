#ifndef TOWERDEFENSE_EASE_H
#define TOWERDEFENSE_EASE_H

#include <cmath>
#include <functional>

using Ease = std::function<double(double)>;

template<class T>
inline T getEasedValue(const Ease &ease, T start, T end, double progress) {
    return progress <= 0.f ? start : progress >= 1.f ? end : start + (end - start) * ease(progress);
}

template<class T>
inline T getEasedOffset(const Ease &ease, T start, T end, double progress) {
    return progress <= 0.f ? start : progress >= 1.f ? end : (end - start) * ease(progress);
}

Ease powIn(int N);
Ease powOut(int N);
Ease powInOut(int N);
Ease backIn(double ratio);
Ease backOut(double ratio);
Ease backInOut(double ratio);
Ease elasticIn(double amplitude, double period);
Ease elasticOut(double amplitude, double period);
Ease elasticInOut(double amplitude, double period);

extern Ease
    linear,
    quadIn, quadOut, quadInOut,
    cubicIn, cubicOut, cubicInOut,
    quartIn, quartOut, quartInOut,
    quintIn, quintOut, quintInOut,
    sineIn, sineOut, sineInOut,
    backInDefault, backOutDefault, backInOutDefault,
    bounceIn, bounceOut, bounceInOut,
    elasticInDefault, elasticOutDefault, elasticInOutDefault;

#endif //TOWERDEFENSE_EASE_H
