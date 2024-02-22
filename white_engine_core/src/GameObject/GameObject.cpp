#include "GameObject/GameObject.h"
#include "Component/IComponent.h"
#include "Component/RenderComponent.h"
#include "Component/TransformComponent.h"

GameObject::GameObject(std::string friendlyName,Shape shape) : shape(shape)
{
	matrix = new Matrix();

	AddComponent<TransformComponent>();
	AddComponent<RenderComponent>();

	GetComponent<TransformComponent>()->Start();
	GetComponent<RenderComponent>()->Start();
	
}

GameObject::~GameObject()
{
	for (IComponent* component : Components) {
		component->Destroy();
		delete component;
	}
	delete matrix;

} 

void GameObject::Update(float deltaTime)
{
	for (IComponent* component : Components) {
		component->Update(deltaTime);
	}

}

void GameObject::Render()
{
}

void GameObject::Draw()
{
}

const std::string& GameObject::GetFriendlyName() const
{
	return FriendlyName;
}

void GameObject::ChangeShape(Shape shape)
{
	this->shape = shape;
}

Shape GameObject::GetShape()
{
	return shape;
}


Matrix* GameObject::GetMatrix()
{
	return matrix;
}
