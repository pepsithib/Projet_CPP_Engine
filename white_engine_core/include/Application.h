#pragma once
#include <vector>


class GameObject;
class Scene;


class Application
{
public:
	Application() = default;
	~Application() = default;

	void init(Scene* scene);

	void run();
};

