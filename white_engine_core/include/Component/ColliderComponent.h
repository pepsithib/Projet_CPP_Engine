#pragma once
#include "Component/IComponent.h"
#include "vector"
#include "glm/glm.hpp"	

class TransformComponent;
class PhysicComponent;

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

	std::vector<glm::vec2> m_vertex;
	glm::vec2 center;
	float radius;
	glm::vec2 HitNormal;

private:

	bool polyLine(float x1, float y1, float x2, float y2);
	bool lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	bool _isStatic;
	TransformComponent* transform;
	PhysicComponent* physic;
	
};

