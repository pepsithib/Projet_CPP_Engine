#pragma once

#include<string>

class GameObject;

class IComponent {

public:
	IComponent() = delete;
	IComponent(GameObject& GameObject);

	virtual ~IComponent();

	virtual void Start() = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void Destroy() = 0;

	virtual const std::string GetComponentName() const = 0;


protected:

	GameObject& GetGameObject() const;

private:

	GameObject& Parent;
};