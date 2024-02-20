#pragma once
#ifndef PARSE_H
#define PARSE_H

//#include "flipper.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JSONParser {
public:
    static json serializeFlipper(const Flipper& flipper);
    static Flipper deserializeFlipper(const json& j);
};

#endif // PARSE_H

class Flipper {
private:
    float positionX;
    float positionY;
    float rotation;

public:
    Flipper(float posX, float posY, float rot);

    float getPositionX() const;
    float getPositionY() const;
    float getRotation() const;
};


