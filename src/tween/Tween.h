#ifndef TOWERDEFENSE_TWEEN_H
#define TOWERDEFENSE_TWEEN_H

#ifndef TWEEN_H
#define TWEEN_H

#include "Ease.h"
#include "Util.h"
#include "Properties.h"

template<class T>
class Tween {
    T &obj;
    Properties<T> from, to, diff, curr;
    sf::Time duration, currTime;
    double progress;
    Ease ease;

    void updateVal();

public:
    Tween(T &obj, const Properties<T> &to, sf::Time duration, Ease ease = linear);

    void updateTarget();
    Properties<T> getFrom() const { return from; }
    Properties<T> getTo() const { return to; }
    sf::Time getDuration() const { return duration; }
    Ease &getEase() { return ease; }
    double getProgress() const { return progress; }
    Properties<T> getCurr() const { return curr; }
    bool isCompleted() const { return progress >= 1.0; }
    sf::Time getTimePosition() const {
        return sf::microseconds(static_cast<Int64> (duration.asMicroseconds() * progress));
    }
    void update(sf::Time delta) { currTime += delta; updateVal(); }
    void setTimePosition(sf::Time timePos) { currTime = timePos; updateVal(); }
    void setProgress(double prog) {
        currTime = sf::microseconds(static_cast<Int64> (duration.asMicroseconds() * prog));
        updateVal();
    }
};

#include "tweenImp.inl"

#endif // TWEEN_H


#endif //TOWERDEFENSE_TWEEN_H
