#include "Component/RenderComponent.h"
#include "Component/TransformComponent.h"
#include "GameObject/GameObject.h"
#include "Render/Render.h"


RenderComponent::RenderComponent(GameObject& GameObject) : IComponent(GameObject)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::setTexture(std::string path) {
	delete dataShape->texture;
	dataShape->texture = new Texture(path.c_str());
}

std::string RenderComponent::getTexturePath()
{
	return dataShape->texture->path;
}

/**RenderComponent::Start():
* Setup the necessary step to create buffers and stuff to drawn the Object on the screen
* Fragment Shaders change between a Rectangle/Triangle and a Circle
* 
*/
void RenderComponent::Start()
{
	Matrix* matrix = GetGameObject().GetMatrix();
	Buffers* buf = new Buffers();
	buf->storeData(matrix->GetVertex().v_array, matrix->GetVertex().v_size * sizeof(float));
	Buffers* buf2 = new Buffers();
	buf2->storeData(matrix->GetIndices().i_array, matrix->GetIndices().i_size * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf->GetBuffer(), 0, 7 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	vao->MakeVao(2, 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	/* Create Program */
	glVertexArrayElementBuffer(vao->GetVaoId(), buf2->GetBuffer());

	Shader* shader;

	switch (GetGameObject().GetShape()) {
	case Shape::Circle:
		shader = new Shader(Render::getInstance()->vsSrc, Render::getInstance()->fsSrc_Circle);
		break;
	default:
		shader = new Shader(Render::getInstance()->vsSrc, Render::getInstance()->fsSrc);
		break;
	}

	std::vector<Buffers*>* buffers = new std::vector<Buffers*>;
	buffers->push_back(buf);
	buffers->push_back(buf2);
	Texture* texture = new Texture("../white_engine_core/Texture/dolphin.jpg");
	dataShape = new DataShape(vao, shader, matrix->GetIndices().i_size, buffers, texture);
	Render::getInstance()->m_drawList.push_back(dataShape);
}

void RenderComponent::Update(float deltaTime)
{
}

void RenderComponent::Destroy()
{
	delete dataShape;
}


/**
* Draw():
* Call the drawTriangle from the Render Singleton
*/
void RenderComponent::Draw(GLFWwindow* window)
{
	TransformComponent* transform = GetGameObject().GetComponent<TransformComponent>();
	Render::getInstance()->drawTriangle(window, *dataShape, transform);
}

const std::string RenderComponent::GetComponentName_Static()
{
	return "Renderer";
}

const std::string RenderComponent::GetComponentName() const
{
	return GetComponentName_Static();
}