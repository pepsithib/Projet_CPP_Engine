#pragma once
#include "Component/IComponent.h"

#include "glm/glm.hpp"	

class TransformComponent;

class ColliderComponent :
    public IComponent
{
public:

	ColliderComponent(GameObject& GameObject);
	~ColliderComponent();

	virtual void Start() override;

	virtual void Update(float deltaTime) override;

	virtual void Destroy() override;

	bool isStatic();
	void setStatic();

	bool CollideWith(ColliderComponent* collider);

	static const std::string GetComponentName_Static();
	virtual const std::string GetComponentName() const;



private:

	bool _isStatic;
	TransformComponent* transform;
	glm::vec2 w;
	glm::vec2 h;
	float radius;
};

