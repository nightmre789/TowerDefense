#ifndef TOWERDEFENSE_MISC_H
#define TOWERDEFENSE_MISC_H

#include <SFML/Graphics.hpp>
using namespace sf;

#ifndef PI
#define PI 3.14159265359
#endif

#ifndef PI_2
#define PI_2 6.28318530718
#endif

inline Color operator * (const Color &l, double r) {
    return {
        (Uint8) (l.r * r),
        (Uint8) (l.g * r),
        (Uint8) (l.b * r),
        (Uint8) (l.a * r)
    };
}

template<class T>
inline Rect<T> operator + (const Rect<T> &l, const Rect<T> &r) {
    return {
        l.left + r.left,
        l.top + r.top,
        l.width + r.width,
        l.height + r.height
    };
}

template<class T>
inline Rect<T> operator - (const Rect<T> &l, const Rect<T> &r) {
    return {
        l.left - r.left,
        l.top - r.top,
        l.width - r.width,
        l.height - r.height
    };
}

template<class T>
inline Rect<T> operator * (const Rect<T> &l, double r) {
    return {
        l.left * r,
        l.top * r,
        l.width * r,
        l.height * r
    };
}

template<class T>
inline Vector2<T> operator * (const Vector2<T> &l, double r) {
    return {
        l.x * r,
        l.y * r
    };
}

#endif //TOWERDEFENSE_MISC_H
