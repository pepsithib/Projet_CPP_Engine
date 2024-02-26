#pragma once

#include "File.h"
#include <glm/vec2.hpp>
#include <map>
#include "Texture.h"


class File;
struct GLFWwindow;

struct DataShape;

class Render
{
public:

	/* Struct to stock current draw shape */
	

	Render() = default;
	~Render();



	/* Shape render functions */
	void build(float* vertex,unsigned int v_size,unsigned int* indices,unsigned int i_size,Texture* texture);
	void buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc);
	void setShaders();
	void drawTriangle(GLFWwindow* window, DataShape& shapeToRender, glm::vec2 worldTransform, float Rotation, glm::vec2 Scale);
	void drawCircle();

	static Render* getInstance();

	File* vsSrc;
	File* fsSrc;

	std::vector<DataShape*> m_drawList;

private :
	
};

