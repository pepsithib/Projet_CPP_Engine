#pragma once
#include <vector>

#define DEBUG_INFO_SIZE 30
class GameObject;

class Application
{
public:
	Application() = default;
	~Application() = default;

	void run();

	/**
	 * \brief : Function that display the imgui windows for the editor DEBUG ONLY
	 * \param 
	 *  object : list of Game object to edit : position, rotation, scale, texture can be edit, a gameObject can be delete to
	*/
	void DrawImgui(std::vector<GameObject*> &objects);
};

