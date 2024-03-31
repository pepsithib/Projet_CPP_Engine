#pragma once

#include <string>
#include <vector>
#include "Matrix.h"

class IComponent;


enum class Shape {

	None,
	Circle,
	Rectangle,
	Triangle,
};


class GameObject
{

public :
	GameObject() = default;
	GameObject(std::string friendlyName = "", Shape shape = Shape::None);
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

	/*
	* Adding tag to an object make groups event simplier than just using a unique name
	*/
	bool AddTag(std::string newTag);
	void RemoveTag(std::string TagToRemove);
	bool ContainTag(std::string TagToCheck);
	std::vector<std::string> GetTags();

	Matrix* GetMatrix();

protected:

	std::vector<std::string> tags;
	std::vector<IComponent*> Components;
	std::string FriendlyName;
	Shape shape;
	Matrix* matrix;
};

#include "GameObject.hxx"
