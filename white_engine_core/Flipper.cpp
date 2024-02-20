#include "Flipper.h"

Flipper::Flipper(float posX, float posY, float rot) : positionX(posX), positionY(posY), rotation(rot) {}

float Flipper::getPositionX() const {
    return positionX;
}

float Flipper::getPositionY() const {
    return positionY;
}

float Flipper::getRotation() const {
    return rotation;
}
