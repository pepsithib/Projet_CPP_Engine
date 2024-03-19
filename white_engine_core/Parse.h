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

    /**
    * \brief : Function to store the scene state in a json file
    * \param
    *  sceneToSave : the scene to save
    */
    json serializeFlipper(Scene* sceneToSave);

    /**
    * \brief : Function to reload a scene state from a json file
    * \param
    *  save : the json that contains a scene state
    *  sceneToReload : the scene reference to reaload
    */
    void deserializeFlipper(json& save, Scene& sceneToReload);
private:
    std::vector<std::string> gOnameList;
};

#endif // PARSE_H



