#pragma once
#include <vector>
#include <../Parse.h>
#include "nlohmann/json.hpp"


class GameObject;
class Scene;
class InputManager;
class EventSystem;

class Application
{
public:
	Application() = default;
	~Application() = default;

	void init(Scene* scene, InputManager* IM, EventSystem* ES);

	void run();

	void saveGame(Scene* sceneToSave, JSONParser &parser);
	void loadGame(Scene& sceneToReload, JSONParser &parser);
};

