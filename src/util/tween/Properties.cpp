#include <SFML/Graphics.hpp>
#include "Properties.h"

void Properties<Transformable>::importFrom(const ItemType &obj) {
    position = obj.getPosition();
    scale = obj.getScale();
    origin = obj.getOrigin();
    rotation = obj.getRotation();
}
void Properties<Transformable>::exportTo(ItemType &obj) {
    obj.setOrigin(origin);
    obj.setScale(scale);
    obj.setPosition(position);
    obj.setRotation(rotation);
}

void Properties<Shape>::importFrom(const ItemType &obj) {
    ParentType::importFrom(obj);
    fillColor = obj.getFillColor();
    outlineColor = obj.getOutlineColor();
    outlineThickness = obj.getOutlineThickness();
}

void Properties<Shape>::exportTo(ItemType &obj) {
    ParentType::exportTo(obj);
    obj.setFillColor(fillColor);
    obj.setOutlineColor(outlineColor);
    obj.setOutlineThickness(outlineThickness);
}