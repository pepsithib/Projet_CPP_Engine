#include "TransformComponent.h"
#include "GameObject.h"	
#include <glm/trigonometric.hpp>
#include <iostream>

TransformComponent::TransformComponent(GameObject& GameObject) : IComponent(GameObject)
{
	
	WorldPosition = glm::vec2(0,  0);
	Scale = glm::vec2(1, 1);
	Rotation = 0.0;
	Size = glm::vec2(0.2, 0.2);
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
	Scale = newScale;
}

glm::vec2 TransformComponent::GetScale()
{
	return Scale;
}

void TransformComponent::Start()
{

}

void TransformComponent::Update(float deltaTime)
{

	int nb_of_dot = 0;
	int size = 0;
	switch (GetGameObject().GetShape()) {
	case Triangle:
		nb_of_dot = 3;
		size = nb_of_dot * 7;
		vertex = new float[21]();
		vertex[0] = 0.0f;
		vertex[1] = 0.0f;
		vertex[2] = 0.0f;//R
		vertex[3] = 0.0f;//G
		vertex[4] = 0.0f;//B
		vertex[5] = 1.0f;//S1
		vertex[6] = 1.0f;//T
		vertex[7] = (vertex[0] + Size.x);
		vertex[8] = vertex[1];
		vertex[9] = 0.0f;//R
		vertex[10] = 0.0f;//G
		vertex[11] = 0.0f;//B
		vertex[12] = 1.0f;//S1
		vertex[13] = 0.0f;//T
		vertex[14] = vertex[0];
		vertex[15] = (vertex[1] - Size.y);
		vertex[16] = 0.0f;//R
		vertex[17] = 0.0f;//G
		vertex[18] = 0.0f;//B
		vertex[19] = 0.0f;//S1
		vertex[20] = 0.0f;//T

		break;
	case Rectangle:
		nb_of_dot = 4;
		size = nb_of_dot * 7;
		vertex = new float[28]();
		vertex[0] = 0.0f;
		vertex[1] = 0.0f;
		vertex[2] = 0.0f;//R
		vertex[3] = 0.0f;//G
		vertex[4] = 0.0f;//B
		vertex[5] = 1.0f;//S1
		vertex[6] = 1.0f;//T
		vertex[7] = (vertex[0] + Size.x);
		vertex[8] = vertex[1];
		vertex[9] = 0.0f;//R
		vertex[10] = 0.0f;//G
		vertex[11] = 0.0f;//B
		vertex[12] = 1.0f;//S1
		vertex[13] = 0.0f;//T
		vertex[14] = vertex[0];
		vertex[15] = (vertex[1] - Size.y);
		vertex[16] = 0.0f;//R
		vertex[17] = 0.0f;//G
		vertex[18] = 0.0f;//B
		vertex[19] = 0.0f;//S1
		vertex[20] = 0.0f;//T
		vertex[21] = (vertex[0] + Size.x);
		vertex[22] = (vertex[1] - Size.y);
		vertex[23] = 0.0f;//R
		vertex[24] = 0.0f;//G
		vertex[25] = 0.0f;//B
		vertex[26] = 0.0f;//S1
		vertex[27] = 1.0f;//T
		break;
	case Circle:
		nb_of_dot = 100;
		vertex = new float[nb_of_dot * 2]();
		for (int i = 0; i < (nb_of_dot * 2) + 1; i=i+2) {
			float currentAngle = 360.0f / nb_of_dot * i;
			float x = (Size.x + cos(glm::radians(currentAngle)));
			float y = (Size.y + sin(glm::radians(currentAngle)));
			vertex[i] = x;
			vertex[i + 1] = y;
		}
		break;
	case None:
		nb_of_dot = 0;
		break;
	default:
		nb_of_dot = 0;
		size = 0;
		break;
	}
	//Translation with World Position
	for (int i = 0; i < (nb_of_dot * 7); i = i + 7)
	{

		float x = vertex[i];
		float y = vertex[i + 1];
		vertex[i] = cos(Rotation) * x - sin(Rotation) * y;
		vertex[i + 1] = sin(Rotation) * x + cos(Rotation) * y;

	}
	for (int i = 0; i < (nb_of_dot * 7)-1; i += 7)
	{
		float x = vertex[i];
		float y = vertex[i + 1];
		vertex[i] = x + WorldPosition.x;
		vertex[i + 1] = y + WorldPosition.y;
	}
	//Rotating with Rotation (in radiant)
	
	GetGameObject().UpdateMatrix(vertex,size);
	delete vertex;
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
