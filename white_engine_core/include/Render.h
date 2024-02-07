#pragma once
#include "Vao.h"
#include "../include/File.h"
class Render
{
public:

	/* Struct to stock current draw shape */
	struct DataShape 
	{
		DataShape(Vao* vertices, unsigned int prog, unsigned int vs, unsigned int fs)
		{
			shapeVertices = vertices;
			progamId = prog;
			vertexShader = vs;
			fragmentShader = fs;
		}
		Vao* shapeVertices;
		unsigned int progamId;
		unsigned int fragmentShader;
		unsigned int vertexShader;
	};

	Render() = default;
	~Render();

	/* Shape render functions */
	void buildTriangle(File* vsSrc, File* fsSrc);
	void buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc);
	void buildRectangle(File* vsSrc, File* fsSrc);

	void drawTriangle();
	void drawCircle();

private :
	std::vector<DataShape*> m_drawList;
};

