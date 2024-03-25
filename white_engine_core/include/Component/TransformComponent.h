#pragma once

#include <glm/glm.hpp>
#include <Component/IComponent.h>


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

	void SetSize(glm::vec2 newSize);
	glm::vec2 GetSize();

	void SetPivot(glm::vec2 newPivot);
	glm::vec2 GetPivot();

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
	glm::vec2 Pivot;
};

