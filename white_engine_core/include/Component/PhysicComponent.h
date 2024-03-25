#pragma once
#include "Component/IComponent.h"

#include <glm/glm.hpp>

constexpr auto GRAVITY = -9.81;

class PhysicComponent :
    public IComponent
{

public:

	PhysicComponent(GameObject& GameObject);
	~PhysicComponent();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	void AddForce(glm::vec2 force);
	void AddImpulse(glm::vec2 impulse);

	void setAcceleration(glm::vec2 newAcce);
	glm::vec2 getAcceleration();

	void setVelocity(glm::vec2 newVel);
	glm::vec2 getVelocity();

	bool getGravityEnabled();

	void setGravity();

	bool getStatic();
	void setStatic();

	static const std::string GetComponentName_Static();
	virtual const std::string GetComponentName() const override;

private :

	bool _gravityEnabled = true;
	glm::vec2 Velocity;
	glm::vec2 Acceleration;
	bool _isStatic;
};

