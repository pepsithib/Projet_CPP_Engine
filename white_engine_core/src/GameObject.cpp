#include "GameObject.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"


GameObject::GameObject(std::string friendlyName,float* matrix,Shape shape) : matrix(matrix),shape(shape)
{
	AddComponent<TransformComponent>();
	AddComponent<RenderComponent>();
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

void GameObject::UpdateMatrix(float* vertex, int size)
{
	delete matrix;
	matrix = new float[size]();
	memcpy(matrix, vertex, sizeof(float) * size);
}

float* GameObject::GetMatrix()
{
	return matrix;
}
