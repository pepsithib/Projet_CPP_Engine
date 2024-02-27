#include "Component/IComponent.h"

IComponent::IComponent(GameObject& GameObject) : Parent{ GameObject } {}

IComponent::~IComponent(){}

GameObject& IComponent::GetGameObject() const
{
	return Parent;
}