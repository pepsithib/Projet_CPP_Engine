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

	/**
	* \brief : Function to initialise scene
	* \param
	*  scene : the scene where the gameObjects will be add
	*  IM : input manager system
	*  ES : event system
	*/
	void init(Scene* scene, InputManager* IM, EventSystem* ES);

	/**
	* \brief : Function to execute gameplay logic
	*/
	void run();

	/**
	* \brief : Function to initialise scene
	* \param
	*  sceneToSave : scene that will be save in json file
	*  parser : json object (use to serialise)
	*/
	void saveGame(Scene* sceneToSave, JSONParser &parser);

	/**
	* \brief : Function to initialise scene
	* \param
	*  sceneToReload : the scene where the save file will be reload
	*  parser : json object (use to serialise)
	*/
	void loadGame(Scene& sceneToReload, JSONParser &parser);
};

