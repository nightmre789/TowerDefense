#include "Tween.h"
#include <string>

template<class T>
struct GetProperty {
    std::string sig;
    T val;
    bool found;

    GetProperty(std::string sig) : sig(sig), found(false) {}

    void operator()(T &t, std::string sign) {
        if (sign == sig) {
            val = t;
            found = true;
        }
    }

    template<class AnyType>
    void operator()(AnyType &, std::string) {}
};

template<class PropType, class ObjType>
inline PropType getProperty(Properties <ObjType> &props, std::string sign) {
    GetProperty<PropType> gp(sign);
    props.forEachProperty(gp);
    return gp.val;
}

template<class T>
struct SetProperty {
    std::string sig;
    T val;
    bool found;

    SetProperty(std::string sig, const T &val) : sig(sig), val(val), found(false) {}

    void operator()(T &t, std::string sign) {
        if (sign == sig) {
            t = val;
            found = true;
        }
    }

    template<class AnyType>
    void operator()(AnyType &, std::string) {}
};

template<class PropType, class ObjType>
inline void setProperty(Properties <ObjType> &props, std::string sign, PropType val) {
    SetProperty<PropType> gp(sign, val);
    props.forEachProperty(gp);
}

////

template<class ObjType>
struct CalcDiff {
    Properties <ObjType> from, to, diff;

    template<class PropType>
    void operator()(PropType &toProp, std::string sig) {
        PropType diffProp = toProp - getProperty<PropType>(from, sig);
        setProperty(diff, sig, diffProp);
    }
};

template<class ObjType>
inline Properties <ObjType> calcDiff(Properties <ObjType> &o1, Properties <ObjType> &o2) {
    CalcDiff<ObjType> obj;
    obj.diff = obj.from = o2;
    obj.to = o1;
    o1.forEachProperty(obj);
    return obj.diff;
}

template<class ObjType>
struct CalcSum {
    Properties <ObjType> o1, o2, sum;

    template<class PropType>
    void operator()(PropType &o1Prop, std::string sig) {
        PropType sumProp = o1Prop + getProperty<PropType>(o2, sig);
        setProperty(sum, sig, sumProp);
    }
};

template<class ObjType>
inline Properties <ObjType> calcSum(Properties <ObjType> &o1, Properties <ObjType> &o2) {
    CalcSum<ObjType> obj;
    obj.sum = obj.o1 = o1;
    obj.o2 = o2;
    o1.forEachProperty(obj);
    return obj.sum;
}

template<class ObjType>
struct CalcProd {
    Properties <ObjType> o, prod;
    double m;

    template<class PropType>
    void operator()(PropType &o1Prop, std::string sig) {
        PropType prodProp = o1Prop * m;
        setProperty(prod, sig, prodProp);
    }
};

template<class ObjType>
inline Properties <ObjType> calcProd(Properties <ObjType> &o, double m) {
    CalcProd<ObjType> obj;
    obj.prod = obj.o = o;
    obj.m = m;
    o.forEachProperty(obj);
    return obj.prod;
}

////

template<class T>
Tween<T>::Tween(T &obj, const Properties <T> &to, sf::Time duration, Ease ease)
        : obj(obj), to(to), duration(duration), progress(0.0), ease(ease) {
    updateTarget();
}

template<class T>
void Tween<T>::updateTarget() {
    from.importFrom(obj);
    curr = from;

    diff = calcDiff(to, from);
}

template<class T>
void Tween<T>::updateVal() {
    progress = currTime / duration;

    if (progress >= 1.0) progress = 1.0;

    double ev = ease(progress);
    Properties <T> prod = calcProd(diff, ev);
    curr = calcSum(from, prod);

    curr.exportTo(obj);
}
