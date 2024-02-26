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
