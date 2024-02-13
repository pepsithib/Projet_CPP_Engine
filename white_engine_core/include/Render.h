#pragma once
#include "Vao.h"
#include "Buffers.h"
#include "../include/File.h"
#include <glm/vec3.hpp>
#include <map>
class Render
{
public:

	/* Struct to stock current draw shape */
	struct DataShape 
	{
		DataShape(Vao* vertices, unsigned int prog, unsigned int vs, unsigned int fs, GLsizei size)
		{
			shapeVertices = vertices;
			progamId = prog;
			vertexShader = vs;
			fragmentShader = fs;
			count = size;
			buf = nullptr;
		}

		DataShape(Vao* vertices, unsigned int prog, unsigned int vs, unsigned int fs, GLsizei size, Buffers* buffer)
		{
			shapeVertices = vertices;
			progamId = prog;
			vertexShader = vs;
			fragmentShader = fs;
			count = size;
			buf = buffer;
		}

		~DataShape()
		{
			delete shapeVertices;
			glDeleteProgram(progamId);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			if (buf != nullptr)
				delete buf;
		}

		Vao* shapeVertices;
		unsigned int progamId;
		unsigned int fragmentShader;
		unsigned int vertexShader;
		GLsizei count;
		Buffers* buf;
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

