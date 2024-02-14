#pragma once
#include "Vao.h"
#include "Buffers.h"
#include "../include/File.h"
#include <glm/vec3.hpp>
#include <map>
#include <Texture.h>

class Shader;
class Vao;
class Buffers;
class File;

class Render
{
public:

	/* Struct to stock current draw shape */
	struct DataShape 
	{

		DataShape(Vao* vertices, Shader* shader, GLsizei size, std::vector<Buffers*> *buffers)
		{
			shapeVertices = vertices;
			count = size;
			buf = buffers;
			shaders = shader;
		}

		~DataShape()
		{
			delete shapeVertices;
			delete shaders;
			delete texture;

			if (!buf->empty())
			{
				for (auto i : *buf)
				{
					delete i;
				}
				delete buf;
			}

		}

		Vao* shapeVertices;
		Shader* shaders;
		GLsizei count;
		Texture* texture = new Texture("../white_engine_core/Texture/container.jpg");
		std::vector<Buffers*> *buf;
	};

	Render() = default;
	~Render();

	/* Shape render functions */
	void buildTriangle(File* vsSrc, File* fsSrc,float x, float y);
	void buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc);
	void buildRectangle(File* vsSrc, File* fsSrc, float x, float y);

	void drawTriangle();
	void drawCircle();

	static Render* getInstance();

private :
	std::vector<DataShape*> m_drawList;
};

