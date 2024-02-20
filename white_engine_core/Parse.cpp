#include "Parse.h"

json JSONParser::serializeFlipper(const Flipper& flipper) {
    return {
        {"positionX", flipper.getPositionX()},
        {"positionY", flipper.getPositionY()},
        {"rotation", flipper.getRotation()}
    };
}

Flipper JSONParser::deserializeFlipper(const json& j) {
    return Flipper(j["positionX"], j["positionY"], j["rotation"]);
}


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