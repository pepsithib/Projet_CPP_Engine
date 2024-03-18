#pragma once
#ifndef PARSE_H
#define PARSE_H

#include "nlohmann/json.hpp"
#include <vector>
class Scene;

using json = nlohmann::json;

class JSONParser {
public:
    JSONParser() = default;
    ~JSONParser() = default;

    json serializeFlipper(Scene* flipper);
    void deserializeFlipper(const json& j, Scene& flipper);
private:
    std::vector<std::string> gOnameList;
};

#endif // PARSE_H



