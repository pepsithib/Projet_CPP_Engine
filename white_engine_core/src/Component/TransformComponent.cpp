#include "Component/TransformComponent.h"
#include "GameObject/GameObject.h"	
#include <glm/trigonometric.hpp>
#include <iostream>

TransformComponent::TransformComponent(GameObject& GameObject) : IComponent(GameObject)
{
	
	WorldPosition = glm::vec2(0,  0);
	Scale = glm::vec2(1, 1);
	Rotation = 0.0;
	Size = glm::vec2(0.2, -0.2);
}

TransformComponent::~TransformComponent()
{
}

void TransformComponent::SetWorldPosition(glm::vec2 newPosition)
{
	WorldPosition = newPosition;
}

glm::vec2 TransformComponent::GetWorldPosition()
{
	return WorldPosition;
}

void TransformComponent::SetRotation(float newRotation)
{
	Rotation = newRotation;
}

float TransformComponent::GetRotation()
{
	return Rotation;
}

void TransformComponent::SetScale(glm::vec2 newScale)
{
	switch(GetGameObject().GetShape()) {
		case Circle:
			Scale = glm::vec2(newScale.x);
			break;
		default:
			Scale = newScale;
			break;
	}
	
}

glm::vec2 TransformComponent::GetScale()
{
	return Scale;
}

void TransformComponent::SetSize(glm::vec2 newSize)
{
	Size = newSize;
}

glm::vec2 TransformComponent::GetSize()
{
	return Size;
}

void TransformComponent::Start()
{
	unsigned int v_size = 0;
	unsigned int i_size = 0;
	switch (GetGameObject().GetShape()) {
	case Shape::Triangle:
		v_size = 21;
		i_size = 3;
		break;
	case Shape::Rectangle:
		v_size = 28;
		i_size = 6;
		break;
	case Shape::Circle:
		v_size = 28;
		i_size = 6;
		break;
	default:
		v_size = 0;
		i_size = 0;
	}
	float* vertex = new float[v_size];
	unsigned int* indices = new unsigned int[i_size];
	switch (GetGameObject().GetShape()) {
	case Shape::Triangle:
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		vertex[0] = 0.0f;
		vertex[1] = 0.0f;
		vertex[2] = 0.0f;//R
		vertex[3] = 0.0f;//G
		vertex[4] = 0.0f;//B
		vertex[5] = 0.0f;//S
		vertex[6] = 1.0f;//T
		vertex[7] = (vertex[0] + Size.x);
		vertex[8] = vertex[1];
		vertex[9] = 0.0f;//R
		vertex[10] = 0.0f;//G
		vertex[11] = 0.0f;//B
		vertex[12] = 0.0f;//S
		vertex[13] = 0.0f;//T
		vertex[14] = vertex[0];
		vertex[15] = (vertex[1] + Size.y);
		vertex[16] = 0.0f;//R
		vertex[17] = 0.0f;//G
		vertex[18] = 0.0f;//B
		vertex[19] = 1.0f;//S
		vertex[20] = 0.0f;//T

		break;
	case Shape::Rectangle:
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;
		vertex[0] = 0.0f;
		vertex[1] = 0.0f;
		vertex[2] = 0.0f;//R
		vertex[3] = 0.0f;//G
		vertex[4] = 0.0f;//B
		vertex[5] = 1.0f;//S1
		vertex[6] = 1.0f;//T
		vertex[7] = vertex[0] + Size.x;
		vertex[8] = vertex[1];
		vertex[9] = 0.0f;//R
		vertex[10] = 0.0f;//G
		vertex[11] = 0.0f;//B
		vertex[12] = 0.0f;//S1
		vertex[13] = 1.0f;//T
		vertex[14] = vertex[0];
		vertex[15] = vertex[1] +Size.y;
		vertex[16] = 0.0f;//R
		vertex[17] = 0.0f;//G
		vertex[18] = 0.0f;//B
		vertex[19] = 1.0f;//S1
		vertex[20] = 0.0f;//T
		vertex[21] = vertex[0] + Size.x;
		vertex[22] = vertex[1] + Size.y;
		vertex[23] = 0.0f;//R
		vertex[24] = 0.0f;//G
		vertex[25] = 0.0f;//B
		vertex[26] = 0.0f;//S1
		vertex[27] = 0.0f;//T
		break;
	case Shape::Circle:
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 1;
		indices[4] = 2;
		indices[5] = 3;
		vertex[0] = 0.0f;
		vertex[1] = 0.0f;
		vertex[2] = 0.0f;//R
		vertex[3] = 0.0f;//G
		vertex[4] = 0.0f;//B
		vertex[5] = 1.0f;//S1
		vertex[6] = 1.0f;//T
		vertex[7] = vertex[0] + Size.x;
		vertex[8] = vertex[1];
		vertex[9] = 0.0f;//R
		vertex[10] = 0.0f;//G
		vertex[11] = 0.0f;//B
		vertex[12] = 0.0f;//S1
		vertex[13] = 1.0f;//T
		vertex[14] = vertex[0];
		vertex[15] = vertex[1] + Size.y;
		vertex[16] = 0.0f;//R
		vertex[17] = 0.0f;//G
		vertex[18] = 0.0f;//B
		vertex[19] = 1.0f;//S1
		vertex[20] = 0.0f;//T
		vertex[21] = vertex[0] + Size.x;
		vertex[22] = vertex[1] + Size.y;
		vertex[23] = 0.0f;//R
		vertex[24] = 0.0f;//G
		vertex[25] = 0.0f;//B
		vertex[26] = 0.0f;//S1
		vertex[27] = 0.0f;//T
		break;
	case Shape::None:
		break;
	default:
		v_size = 0;
		i_size = 0;
		break;
	}

	GetGameObject().GetMatrix()->SetVertex(vertex, v_size);
	GetGameObject().GetMatrix()->SetIndices(indices, i_size);
	delete[] vertex;
	delete[] indices;
}

void TransformComponent::Update(float deltaTime)
{
}

void TransformComponent::Destroy()
{
}

const std::string TransformComponent::GetComponentName_Static()
{
	return "Transform";
}

const std::string TransformComponent::GetComponentName() const
{
	return GetComponentName_Static();
}
