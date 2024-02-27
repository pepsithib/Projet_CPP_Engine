#include "Component/ColliderComponent.h"
#include "GameObject/GameObject.h"
#include "Component/TransformComponent.h"

ColliderComponent::ColliderComponent(GameObject& GameObject) : IComponent(GameObject)
{
	transform = GetGameObject().GetComponent<TransformComponent>();

}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Start()
{
	
}

void ColliderComponent::Update(float deltaTime)
{
	glm::mat2 matRot(cos(transform->GetRotation()), -sin(transform->GetRotation()), sin(transform->GetRotation()), cos(transform->GetRotation()));
	w = (matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x,0.0) * transform->GetScale();
	h = (matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x, 0.0) * transform->GetScale();

}	
void ColliderComponent::Destroy()
{
}

bool ColliderComponent::isStatic()
{
	return _isStatic;
}

void ColliderComponent::setStatic()
{
	if (_isStatic) {
		_isStatic = false;
	}
	else {
		_isStatic = true;
	}
}

bool ColliderComponent::CollideWith(ColliderComponent* collider)
{
	if (_isStatic) { return false; }


	return true;
}

const std::string ColliderComponent::GetComponentName_Static()
{
	return "Collider";
}

const std::string ColliderComponent::GetComponentName() const
{
	return GetComponentName_Static();
}
