#include "Component/ColliderComponent.h"
#include "GameObject/GameObject.h"
#include "Component/TransformComponent.h"
#include "Component/PhysicComponent.h"
#include <iostream>

ColliderComponent::ColliderComponent(GameObject& GameObject) : IComponent(GameObject)
{
	transform = GetGameObject().GetComponent<TransformComponent>();
	physic = GetGameObject().GetComponent<PhysicComponent>();
	glm::mat2 matRot(cos(transform->GetRotation()), -sin(transform->GetRotation()), sin(transform->GetRotation()), cos(transform->GetRotation()));
	m_vertex.push_back(glm::vec2(0.0));
	m_vertex.push_back(glm::vec2(1.0));
	m_vertex.push_back(glm::vec2(2.0));
	m_vertex.push_back(glm::vec2(3.0));
	_isStatic = false;
	center = transform->GetWorldPosition();
	radius = 0.1;
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Start()
{
	
}

/*Update the current collision box to match the 4 point of the GameObject*/
void ColliderComponent::Update(float deltaTime)
{

	int width = 550;
	int height = 800;
	center = (transform->GetWorldPosition()) + (physic->getVelocity() * deltaTime);
	glm::mat2 matRot(cos(transform->GetRotation()), -sin(transform->GetRotation()), sin(transform->GetRotation()), cos(transform->GetRotation())); 
	
	/*Take the transform and the physic to */
	m_vertex.at(0) = (((matRot * ( glm::vec2(-.1,.1)		* transform->GetScale()		+ - transform->GetPivot())) - - transform->GetPivot())	+ (transform->GetWorldPosition()) + (physic->getVelocity() * deltaTime))	/ glm::vec2(float(width) / float(height), 1);
	m_vertex.at(1) = (((matRot * ( glm::vec2(.1,.1)			* transform->GetScale()		+ - transform->GetPivot())) - - transform->GetPivot())	+ (transform->GetWorldPosition()) + (physic->getVelocity() * deltaTime))	/ glm::vec2(float(width) / float(height), 1);
	m_vertex.at(2) = (((matRot * ( glm::vec2(.1,-.1)		* transform->GetScale()		+ - transform->GetPivot())) - - transform->GetPivot())	+ (transform->GetWorldPosition()) + (physic->getVelocity() * deltaTime))	/ glm::vec2(float(width) / float(height), 1);
	m_vertex.at(3) = (((matRot * ( glm::vec2(-.1,-.1)		* transform->GetScale()		+ - transform->GetPivot())) - - transform->GetPivot())	+ (transform->GetWorldPosition()) + (physic->getVelocity() * deltaTime))	/ glm::vec2(float(width) / float(height), 1);
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

double triangleArea(glm::vec2 AB, glm::vec2 AC) {
	return abs((AB.x * AC.y) - (AB.y * AC.x)) / 2.0;
}


bool ColliderComponent::polyLine(float x1, float y1, float x2, float y2) {

	float min_dist = 0;
	float max_dist = 0;
	switch (GetGameObject().GetShape()) {
	
	/*case Shape::Circle:
		
		glm::vec2 op(x1 - center.x, y1 - center.y);
		glm::vec2 oq(x2 - center.x, y2 - center.y);
		glm::vec2 pq(x2 - x1, y2 - y1);
		glm::vec2 qp(x1 - x2, y1 - y2);
		min_dist = 0;
		
		max_dist = glm::max(glm::length(op), glm::length(oq));

		if (glm::dot(op, pq) > 0 && dot(oq, qp) > 0) {
			min_dist = (2 * triangleArea(op, oq)) / glm::length(pq);
		}
		else {
			min_dist = glm::min(glm::length(op), glm::length(oq));
		}
		if (min_dist <= radius && max_dist >= radius) {
			glm::vec2 vector(x2 - x1, y2 - y1);
			HitNormal = glm::normalize(glm::vec2(-vector.y, vector.x));
			return true;
		}
		else {
			HitNormal = glm::vec2(0.0);
			return false;
		}
		break;
	*/
	default:
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

		
		break;


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
		glm::vec2 p1(x1, y1);
		glm::vec2 p2(x2, y2);
		glm::vec2 vector(x2 - x1, y2 - y1);
		HitNormal = glm::normalize(glm::vec2(-vector.y, vector.x));
		return true;
	}
	HitNormal = glm::vec2(0.0);
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
