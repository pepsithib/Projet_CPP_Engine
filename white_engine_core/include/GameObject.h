#pragma once

#include <string>
#include <vector>

class IComponent;

enum Shape {

	None,
	Circle,
	Rectangle,
	Triangle,
};


class GameObject
{

public :
	GameObject() = default;
	GameObject(std::string friendlyName = "",float* matrix = {}, Shape shape = Shape::None);
	~GameObject();

	void Update(float deltaTime);

	void Render();

	void Draw();

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;

	const std::string& GetFriendlyName() const;

	void ChangeShape(Shape shape);
	Shape GetShape();

	void UpdateMatrix(float *vertex, int size);
	float* GetMatrix();

protected:

	std::vector<IComponent*> Components;
	std::string FriendlyName;
	Shape shape;
	float* matrix;
};

#include "GameObject.hxx"
