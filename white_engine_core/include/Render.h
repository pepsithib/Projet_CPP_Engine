#pragma once
#include "Vao.h"
#include "Buffers.h"
#include "../include/File.h"
#include <glm/vec3.hpp>
#include <map>
#include "Texture.h"
#include "Shader.h"


class File;


class Render
{
public:

	/* Struct to stock current draw shape */
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
		}

		Vao* shapeVertices;
		Texture* texture;
		Shader* shaders;
		GLsizei count;
		
		std::vector<Buffers*> *buf;
	};

	Render() = default;
	~Render();



	/* Shape render functions */
	void buildTriangle(float* vertex,Texture* texture);
	void buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc);
	void buildRectangle(File* vsSrc, File* fsSrc, float x, float y);
	void setShaders();
	void drawTriangle();
	void drawCircle();

	static Render* getInstance();

private :
	std::vector<DataShape*> m_drawList;

	File* vsSrc;
	File* fsSrc;
};

