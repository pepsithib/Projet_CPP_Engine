#include "Render.h"
#include "Buffers.h"
#include "Shader.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <Texture.h>

Render::~Render()
{
	for (DataShape* shapeToDelete : m_drawList)
	{
		delete shapeToDelete;
	}

}

void Render::buildTriangle(File* vsSrc, File* fsSrc, float x, float y)
{
	float vertices[21] = {
	 0.0f + x,  0.5f + y, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
	-0.5f + x, -0.5f + y, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	 0.5f + x, -0.5f + y, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f
	};

	unsigned int indices[3] = { 0, 1, 2 };

	/* Allocate brut memory on GPU */ 
	Buffers* buf = new Buffers();
	buf->storeData(vertices, 21 * sizeof(float));
	Buffers* buf2 = new Buffers();
	buf2->storeData(indices, 3 * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf->GetBuffer(), 0, 7 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	vao->MakeVao(2, 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	/* Create Program */
	glVertexArrayElementBuffer(vao->GetVaoId(), buf2->GetBuffer());

	Shader* shader = new Shader(vsSrc, fsSrc);

	std::vector<Buffers*> *buffers = new std::vector<Buffers*>;
	buffers->push_back(buf);
	buffers->push_back(buf2);
	m_drawList.push_back(new DataShape(vao, shader, 3, buffers));
}

void Render::buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc)
{
	std::vector<glm::vec3> vertices;

	/* Calculate theta angle, witch  is use to draw the triangles */
	float angle = 360.0f / dotNumbers;

	int triangleCount = dotNumbers - 2;

	/* Triangle position storage */
	std::vector<glm::vec3> temp;

	/* Calculate position of each triangles */
	for (int i = 0; i < dotNumbers; i++)
	{
		float currentAngle = angle * i;
		float x = radius * cos(glm::radians(currentAngle));
		float y = radius * sin(glm::radians(currentAngle));
		float z = 0.0f;

		temp.push_back(glm::vec3(x, y, z));
	}

	/* Store triangle point in vertice array with an offset of 3 */
	for (int i = 0; i < triangleCount; i++)
	{
		vertices.push_back(temp[0]);
		vertices.push_back(temp[i + 1]);
		vertices.push_back(temp[i + 2]);
	}

	/* Create Program */

	Shader* shader = new Shader(vsSrc, fsSrc);

	// buffer

	Buffers* buf = new Buffers(1);
	Vao* vao = new Vao();

	glBindVertexArray(vao->GetVaoId());
	buf->bind();


	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // asd

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	std::vector<Buffers*>* buffers = new std::vector<Buffers*>;
	buffers->push_back(buf);

	m_drawList.push_back(new DataShape(vao, shader, vertices.size(), buffers));
}

void Render::buildRectangle(File* vsSrc, File* fsSrc, float x, float y)
{
	float vertices[28] = {
	 0.5f + x,  0.5f + y, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
	 0.5f + x,  -0.5f + y, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
	-0.5f + x, -0.5f + y, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	 -0.5f + x,  0.5f + y, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[6] = { 0, 1, 3, 1, 2, 3 };

	/* Allocate brut memory on GPU */
	Buffers* buf = new Buffers();
	buf->storeData(vertices, 28 * sizeof(float));
	Buffers* buf2 = new Buffers();
	buf2->storeData(indices, 6 * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf->GetBuffer(), 0, 7 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	vao->MakeVao(2, 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	glVertexArrayElementBuffer(vao->GetVaoId(), buf2->GetBuffer());

	/* Create Program */
	Shader* shader = new Shader(vsSrc,fsSrc);

	std::vector<Buffers*>* buffers = new std::vector<Buffers*>;
	buffers->push_back(buf);
	buffers->push_back(buf2);

	m_drawList.push_back(new DataShape(vao, shader, 6, buffers));
}

void Render::drawTriangle()
{
	for (DataShape* shapeToRender : m_drawList)
	{
		glBindTexture(GL_TEXTURE_2D, shapeToRender->texture->textureId);
		glBindVertexArray(shapeToRender->shapeVertices->GetVaoId());
		glUseProgram(shapeToRender->shaders->programId);
		glDrawElements(GL_TRIANGLES, shapeToRender->count, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);
	}

}

void Render::drawCircle()
{
	for (DataShape* shapeToRender : m_drawList)
	{
		glBindVertexArray(shapeToRender->shapeVertices->GetVaoId());
		glUseProgram(shapeToRender->shaders->programId);
		glDrawArrays(GL_TRIANGLES, 0, shapeToRender->count);
		glUseProgram(0);
		glBindVertexArray(0);
	}
}

Render* Render::getInstance()
{
	static Render instance;
	return &instance;
}
