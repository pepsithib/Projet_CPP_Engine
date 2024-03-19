#pragma once
#include <vector>
#include <../Parse.h>
#include "nlohmann/json.hpp"


class GameObject;

class Application
{
public:
	Application() = default;
	~Application() = default;

	void run();

	void saveGame(Scene* sceneToSave, JSONParser &parser);
	void loadGame(Scene& sceneToReload, JSONParser &parser);
};

