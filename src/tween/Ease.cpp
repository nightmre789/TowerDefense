#include "Ease.h"
#include "../util/Util.h"

#define lambda(d) [] (double d) -> double

inline double getPowIn(double d, int N) {
    return std::pow(d, N);
}

inline double getPowOut(double d, int N) {
    return 1 - std::pow(1 - d, N);
}

inline double getPowInOut(double t, int N) {
    if ((t *= 2) < 1) return 0.5 * std::pow(t, N);
    else return 1 - 0.5 * std::abs(std::pow(2 - t, N));
}

inline double getBackIn(double t, double a) {
    return t * t * ((a + 1) * t - a);
}

inline double getBackOut(double t, double a) {
    --t;
    return (t * t * ((a + 1) * t + a) + 1);
}

inline double getBackInOut(double t, double a) {
    a *= 1.525;
    if ((t *= 2) < 1) return 0.5 * (t * t * ((a + 1) * t - a));
    else {
        t -= 2;
        return 0.5 * (t * t * ((a + 1) * t + a) + 2);
    }
}

inline double getElasticIn(double t, double amplitude, double period) {
    if (t == 0 || t == 1) return t;
    double s = period / PI_2 * std::asin(1 / amplitude);
    t -= 1;
    return -(amplitude * std::pow(2, 10 * t) * std::sin((t - s) * PI_2 / period));
}

inline double getElasticOut(double t, double amplitude, double period) {
    if (t == 0 || t == 1) return t;
    double s = period / PI_2 * std::asin(1 / amplitude);
    return (amplitude * std::pow(2, -10 * t) * std::sin((t - s) * PI_2 / period) + 1);
}

inline double getElasticInOut(double t, double amplitude, double period) {
    static double pi2 = PI * 2;
    double s = period / pi2 * std::asin(1 / amplitude);
    t *= 2;
    if (t < 1) {
        t -= 1;
        return -0.5 * (amplitude * std::pow(2, 10 * t) * std::sin((t - s) * pi2 / period));
    }
    t -= 1;
    return amplitude * std::pow(2, -10 * (t)) * std::sin((t - s) * pi2 / period) * 0.5 + 1;
}

inline double getBounceOut(double p) {
    if (p < 4 / 11.0) {
        return (121 * p * p) / 16.0;
    } else if (p < 8 / 11.0) {
        return (363 / 40.0 * p * p) - (99 / 10.0 * p) + 17 / 5.0;
    } else if (p < 9 / 10.0) {
        return (4356 / 361.0 * p * p) - (35442 / 1805.0 * p) + 16061 / 1805.0;
    } else {
        return (54 / 5.0 * p * p) - (513 / 25.0 * p) + 268 / 25.0;
    }
}

inline double getBounceIn(double t) {
    return 1 - getBounceOut(1 - t);
}

inline double getBounceInOut(double p) {
    if (p < 0.5) {
        return 0.5 * getBounceIn(p * 2);
    } else {
        return 0.5 * getBounceOut(p * 2 - 1) + 0.5;
    }
}

template<int N>
double getPowIn(double d) {
    return getPowIn(d, N);
}

template<int N>
double getPowOut(double d) {
    return getPowOut(d, N);
}

template<int N>
double getPowInOut(double d) {
    return getPowInOut(d, N);
}

template<int N, int D>
double getBackIn(double d) {
    return getBackIn(d, N / D);
}

template<int N, int D>
double getBackOut(double d) {
    return getBackOut(d, N / D);
}

template<int N, int D>
double getBackInOut(double d) {
    return getBackInOut(d, N / D);
}

Ease
        linear = Ease(lambda(d) { return d; }),
        sineIn = Ease(lambda(d) { return 1 - std::cos(d * PI / 2); }),
        sineOut = Ease(lambda(d) { return std::sin(d * PI / 2); }),
        sineInOut = Ease(lambda(d) { return -0.5 * (std::cos(PI * d) - 1); }),

        backInDefault = Ease(getBackIn<17, 10>),
        backOutDefault = Ease(getBackOut<17, 10>),
        backInOutDefault = Ease(getBackInOut<17, 10>),

        bounceIn = Ease(getBounceIn),
        bounceOut = Ease(getBounceOut),
        bounceInOut = Ease(getBounceInOut),

        elasticInDefault = Ease(elasticIn(1, 0.3)),
        elasticOutDefault = Ease(elasticOut(1, 0.3)),
        elasticInOutDefault = Ease(elasticInOut(1, 0.3 * 1.5));

Ease powIn(int N) {
    return Ease([=] (double d) mutable -> double {
        return getPowIn(d, N);
    });
}

Ease powOut(int N) {
    return Ease([=] (double d) mutable -> double {
        return getPowOut(d, N);
    });
}

Ease powInOut(int N) {
    return Ease([=] (double d) mutable -> double {
        return getPowInOut(d, N);
    });
}

Ease backIn(double ratio) {
    return Ease([=] (double d) mutable -> double {
        return getBackIn(d, ratio);
    });
}

Ease backOut(double ratio) {
    return Ease([=] (double d) mutable -> double {
        return getBackOut(d, ratio);
    });
}

Ease backInOut(double ratio) {
    return Ease([=] (double d) mutable -> double {
        return getBackInOut(d, ratio);
    });
}

Ease elasticIn(double amplitude, double period) {
    return Ease([=] (double d) mutable -> double {
        return getElasticIn(d, amplitude, period);
    });
}

Ease elasticOut(double amplitude, double period) {
    return Ease([=] (double d) mutable -> double {
        return getElasticOut(d, amplitude, period);
    });
}

Ease elasticInOut(double amplitude, double period) {
    return Ease([=] (double d) mutable -> double {
        return getElasticInOut(d, amplitude, period);
    });
}