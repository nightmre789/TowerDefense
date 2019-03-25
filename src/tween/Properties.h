#ifndef TOWERDEFENSE_PROPERTIES_H
#define TOWERDEFENSE_PROPERTIES_H

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

template<class T>
struct Properties {
    using ItemType = T;
    using SelfType = Properties<T>;
};

template<>
struct Properties<Transformable> {
    using ItemType = Transformable;
    using SelfType = Properties<Transformable>;

    Vector2f position, scale, origin;
    float rotation{};

public:
    Properties(const Transformable &obj) { importFrom(obj); }
    Properties() = default;

    void importFrom(const Transformable &obj);
    void exportTo(Transformable &obj);

    template<class F>
    void forEachProperty(F &f) {
        f(position, "Transformable|position");
        f(scale, "Transformable|scale");
        f(origin, "Transformable|origin");
        f(rotation, "Transformable|rotation");
    }
};

template<>
struct Properties<Shape> : Properties<Transformable> {
    using ItemType = Shape;
    using SelfType = Properties<Shape>;
    using ParentType = Properties<Transformable>;

    Color fillColor, outlineColor;
    float outlineThickness{};

public:
    Properties(const ItemType &obj) : ParentType(obj) { importFrom(obj); }
    Properties() = default;

    void importFrom(const ItemType &obj);
    void exportTo(ItemType &obj);

    template<class F>
    void forEachProperty(F &f) {
        ParentType::forEachProperty(f);
        f(fillColor, "Shape|fillColor");
        f(outlineColor, "Shape|outlineColor");
        f(outlineThickness, "Shape|outlineThickness");
    }
};

template<>
struct Properties<CircleShape> : Properties<Shape> {
    using ItemType = CircleShape;
    using SelfType = Properties<CircleShape>;
    using ParentType = Properties<Shape>;

    float radius{};
    size_t pointCount{};

public:
    Properties(const CircleShape &obj) : Properties<Shape>(obj) { importFrom(obj); }
    Properties() = default;

    void importFrom(const ItemType &obj) { ParentType::importFrom(obj); pointCount = obj.getPointCount(); radius = obj.getRadius(); }
    void exportTo(ItemType &obj) { ParentType::exportTo(obj); obj.setRadius(radius); obj.setPointCount(pointCount); }

    template<class F>
    void forEachProperty(F &f) {
        ParentType::forEachProperty(f);
        f(radius, "CircleShape|radius");
        f(pointCount, "CircleShape|pointCount");
    }
};

template<>
struct Properties<RectangleShape> : Properties<Shape> {
    using ItemType = RectangleShape;
    using SelfType = Properties<RectangleShape>;
    using ParentType = Properties<Shape>;

    Vector2f size;

public:
    Properties(const ItemType &obj) : ParentType(obj) { importFrom(obj); }
    Properties() = default;

    void importFrom(const ItemType &obj) { ParentType::importFrom(obj); size = obj.getSize(); }
    void exportTo(ItemType &obj) { ParentType::exportTo(obj); obj.setSize(size); }

    template<class F>
    void forEachProperty(F &f) {
        ParentType::forEachProperty(f);
        f(size, "RectangleShape|size");
    }
};

template<>
struct Properties<Text> : Properties<Transformable> {
    using ItemType = Text;
    using SelfType = Properties<Text>;
    using ParentType = Properties<Transformable>;

    unsigned characterSize{};
    Color color;

public:
    Properties(const ItemType &obj) : ParentType(obj) { importFrom(obj); }
    Properties() = default;

    void importFrom(const ItemType &obj) { ParentType::importFrom(obj); characterSize = obj.getCharacterSize(); color = obj.getFillColor(); }
    void exportTo(ItemType &obj) { ParentType::exportTo(obj); obj.setCharacterSize(characterSize); obj.setFillColor(color); }

    template<class F>
    void forEachProperty(F &f) {
        ParentType::forEachProperty(f);
        f(characterSize, "Text|characterSize");
        f(color, "Text|color");
    }
};

#endif //TOWERDEFENSE_PROPERTIES_H