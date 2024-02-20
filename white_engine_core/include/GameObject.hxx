#pragma once

#include "GameObject.h"

template <typename C>
inline C* GameObject::GetComponent() const {

	static_assert(std::is_base_of<IComponent, C>());

	for (auto& component : Components) {
		if (component->GetComponentName() == C::GetComponentName_Static()) {
			return dynamic_cast<C*>(component);
		}
	}

	return nullptr;

}

template <typename C>
inline C* GameObject::AddComponent()
{
	static_assert(std::is_base_of<IComponent, C>());

	if (GetComponent<C>())
	{
		return nullptr;
	}

	C* component = new C(*this);
	Components.push_back(component);
	return component;
}