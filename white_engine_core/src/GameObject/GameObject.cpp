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
	
	FriendlyName = friendlyName;
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
/**
* Add a tag to the tag vector, if the tag is already present, return false
*/
bool GameObject::AddTag(std::string newTag)
{
	for (std::string tag : tags) {
		if (tag == newTag) {
			return false;
		}
	}
	tags.push_back(newTag);
	return true;
}

void GameObject::RemoveTag(std::string TagToRemove)
{
	int i = 0;
	for (std::string tag : tags) {
		if (tag == TagToRemove) {
			tags.erase(tags.begin() + i);
		}
		i++;
	}
}

bool GameObject::ContainTag(std::string TagToCheck)
{
	for (std::string tag : tags) {
		if (tag == TagToCheck) {
			return true;
		}
	}
	return false;
}

std::vector<std::string> GameObject::GetTags()
{
	return tags;
}


Matrix* GameObject::GetMatrix()
{
	return matrix;
}
