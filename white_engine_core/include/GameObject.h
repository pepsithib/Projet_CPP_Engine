#pragma once

#include <string>
#include <vector>

class IComponent;

class GameObject
{

public :
	GameObject(std::string friendlyName = "");
	~GameObject();

	void Update();

	void Render();

	void Draw();

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;

	const std::string& GetFirendlyName() const;

protected:

	std::vector<IComponent*> Components;
	std::string FriendlyName;
};

