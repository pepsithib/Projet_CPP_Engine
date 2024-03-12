#include "Component/ColliderComponent.h"
#include "GameObject/GameObject.h"
#include "Component/TransformComponent.h"
#include <iostream>

ColliderComponent::ColliderComponent(GameObject& GameObject) : IComponent(GameObject)
{
	transform = GetGameObject().GetComponent<TransformComponent>();
	glm::mat2 matRot(cos(transform->GetRotation()), -sin(transform->GetRotation()), sin(transform->GetRotation()), cos(transform->GetRotation()));
	m_vertex.push_back(matRot * transform->GetWorldPosition());
	m_vertex.push_back((matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x, 0.0) * transform->GetScale());
	m_vertex.push_back((matRot * transform->GetWorldPosition()) + glm::vec2(0.0, transform->GetSize().y) * transform->GetScale());
	m_vertex.push_back((matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x, transform->GetSize().y) * transform->GetScale());
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Start()
{
	
}

void ColliderComponent::Update(float deltaTime)
{
	glm::mat2 matRot(cos(transform->GetRotation()), -sin(transform->GetRotation()), sin(transform->GetRotation()), cos(transform->GetRotation()));
	m_vertex.at(0) = (matRot * transform->GetWorldPosition());
	m_vertex.at(1) = (matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x,0.0) * transform->GetScale();
	m_vertex.at(2) = (matRot * transform->GetWorldPosition()) + glm::vec2(0.0, transform->GetSize().y) * transform->GetScale();
	m_vertex.at(3) = (matRot * transform->GetWorldPosition()) + glm::vec2(transform->GetSize().x, transform->GetSize().y) * transform->GetScale();
}	
void ColliderComponent::Destroy()
{
}

bool ColliderComponent::isStatic()
{
	return _isStatic;
}

void ColliderComponent::setStatic()
{
	if (_isStatic) {
		_isStatic = false;
	}
	else {
		_isStatic = true;
	}
}

bool ColliderComponent::CollideWith(ColliderComponent* collider)
{
	if (_isStatic) { return false; }
	// go through each of the vertices, plus the next
	 // vertex in the list
	int next = 0;
	for (int current = 0; current <collider->m_vertex.size(); current++) {

		// get next vertex in list
		// if we've hit the end, wrap around to 0
		next = current + 1;
		if (next == collider->m_vertex.size()) next = 0;

		// get the PVectors at our current position
		// this makes our if statement a little cleaner
		glm::vec2 vc = collider->m_vertex[current];    // c for "current"
		glm::vec2 vn = collider->m_vertex[next];       // n for "next"

		// now we can use these two points (a line) to compare
		// to the other polygon's vertices using polyLine()
		bool collision = polyLine(vc.x, vc.y, vn.x, vn.y);
		if (collision) return true;

	}

	return false;
}

bool ColliderComponent::polyLine(float x1, float y1, float x2, float y2) {
	// go through each of the vertices, plus the next
	  // vertex in the list
	int next = 0;
	for (int current = 0; current < ColliderComponent::m_vertex.size(); current++) {

		// get next vertex in list
		// if we've hit the end, wrap around to 0
		next = current + 1;
		if (next == m_vertex.size()) next = 0;

		// get the PVectors at our current position
		// extract X/Y coordinates from each
		float x3 = m_vertex[current].x;
		float y3 = m_vertex[current].y;
		float x4 = m_vertex[next].x;
		float y4 = m_vertex[next].y;

		// do a Line/Line comparison
		// if true, return 'true' immediately and
		// stop testing (faster)
		bool hit = lineLine(x1, y1, x2, y2, x3, y3, x4, y4);
		if (hit) {
			return true;
		}
	}

	// never got a hit
	return false;
};

bool ColliderComponent::lineLine(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	// calculate the direction of the lines
	float uA = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));
	float uB = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / ((y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
		return true;
	}
	return false;
}

const std::string ColliderComponent::GetComponentName_Static()
{
	return "Collider";
}

const std::string ColliderComponent::GetComponentName() const
{
	return GetComponentName_Static();
}
