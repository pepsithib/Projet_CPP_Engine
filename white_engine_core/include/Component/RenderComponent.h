#pragma once
#include "Component/IComponent.h"
#include "Render/Texture.h"
#include "Render/Vao.h"
#include "Render/Buffers.h"
#include "Render/Shader.h"
#include <vector>

class TransformComponent;
class IDrawable;

struct DataShape
{

	DataShape(Vao* vertices, Shader* shader, GLsizei size, std::vector<Buffers*>* buffers, Texture* newTexture)
	{
		shapeVertices = vertices;
		count = size;
		buf = buffers;
		texture = newTexture;
		shaders = shader;
	}
	~DataShape()
	{
		delete shapeVertices;
		delete shaders;
		if (!buf->empty())
		{
			for (auto i : *buf)
			{
				delete i;
			}
		}
		delete buf;
		delete texture;
	}

	Vao* shapeVertices;
	Texture* texture;
	Shader* shaders;
	GLsizei count;

	std::vector<Buffers*>* buf;
};

class RenderComponent :
    public IComponent
{




public:

    RenderComponent(GameObject& GameObject);
    ~RenderComponent();

    void setTexture(std::string path);
	std::string getTexturePath();

    virtual void Start() override;

    virtual void Update(float deltaTime) override;

    virtual void Destroy() override;

    void Draw(GLFWwindow* window);

    static const std::string GetComponentName_Static();
    virtual const std::string GetComponentName() const override;

private :
	DataShape* dataShape;
};

