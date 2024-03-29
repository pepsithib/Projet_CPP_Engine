#include "Component/PhysicComponent.h"
#include "Component/TransformComponent.h"
#include "GameObject/GameObject.h"	


PhysicComponent::PhysicComponent(GameObject& GameObject) : IComponent(GameObject)
{
	Velocity = glm::vec2(0, 0);
	Acceleration = glm::vec2(0, 0);
	AddForce(glm::vec2(0, 0));
	_isStatic = false;
}

PhysicComponent::~PhysicComponent()
{
}

void PhysicComponent::Start()
{
}

void PhysicComponent::Update(float deltaTime)
{
	if (!_isStatic) {
		TransformComponent* transform = GetGameObject().GetComponent<TransformComponent>();
		glm::vec2 pos = transform->GetWorldPosition();

		Velocity += (Acceleration  - (Velocity * FRICTION)) * deltaTime;

		pos = pos + (Velocity * deltaTime);

		transform->SetWorldPosition(pos);

		Acceleration = glm::vec2(0.0, GRAVITY);
	}
}

void PhysicComponent::Destroy()
{
}

void PhysicComponent::AddForce(glm::vec2 force) {

	Acceleration += force;
}

void PhysicComponent::AddImpulse(glm::vec2 impulse)
{
	Velocity = Velocity + impulse;
}


void PhysicComponent::setAcceleration(glm::vec2 newAcce)
{
	Acceleration = newAcce;
}

glm::vec2 PhysicComponent::getAcceleration()
{
	return Acceleration;
}

void PhysicComponent::setVelocity(glm::vec2 newVel)
{
	Velocity = newVel;
}

glm::vec2 PhysicComponent::getVelocity()
{
	return Velocity;
}

bool PhysicComponent::getGravityEnabled()
{
	return _gravityEnabled;
}

void PhysicComponent::setGravity()
{
	if (_gravityEnabled)
		_gravityEnabled = false;
	else
		_gravityEnabled = true;
}

bool PhysicComponent::getStatic()
{
	return _isStatic;
}

void PhysicComponent::setStatic()
{
	if (_isStatic) {
		_isStatic = false;
	}
	else {
		_isStatic = true;
	}
}

const std::string PhysicComponent::GetComponentName_Static()
{
	return "Physic";
}

const std::string PhysicComponent::GetComponentName() const
{
	return GetComponentName_Static();
}
