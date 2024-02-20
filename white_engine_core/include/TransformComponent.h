#pragma once

#include <glm/vec2.hpp>
#include <IComponent.h>


class TransformComponent : public IComponent
{

public :

	TransformComponent(GameObject& GameObject);
	~TransformComponent();


	void SetWorldPosition(glm::vec2 newPosition);
	glm::vec2 GetWorldPosition();

	void SetRotation(float newRotation);
	float GetRotation();

	void SetScale(glm::vec2 newScale);
	glm::vec2 GetScale();

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Destroy() override;

	

	static const std::string GetComponentName_Static();
	virtual const std::string GetComponentName() const override;

private :

	glm::vec2 WorldPosition;
	float Rotation;
	glm::vec2 Scale;
	glm::vec2 Size;
	float* vertex;
};

