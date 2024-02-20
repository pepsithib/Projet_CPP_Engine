#pragma once
#ifndef PARSE_H
#define PARSE_H

#include "flipper.h"
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JSONParser {
public:
    static json serializeFlipper(const Flipper& flipper);
    static Flipper deserializeFlipper(const json& j);
};

#endif // PARSE_H


