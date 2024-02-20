#include "RenderComponent.h"
#include "GameObject.h"
#include "Render.h"

RenderComponent::RenderComponent(GameObject& GameObject) : IComponent(GameObject)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::setTexture(std::string path) {
	delete texture;
	texture = new Texture(path.c_str());
}

void RenderComponent::Start()
{
}

void RenderComponent::Update(float deltaTime)
{
	Draw();
}

void RenderComponent::Destroy()
{
	delete texture;
}

void RenderComponent::Draw()
{

	Render::getInstance()->buildTriangle(GetGameObject().GetMatrix(),texture);
}

const std::string RenderComponent::GetComponentName_Static()
{
	return "Renderer";
}

const std::string RenderComponent::GetComponentName() const
{
	return GetComponentName_Static();
}