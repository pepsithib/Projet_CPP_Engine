#include "Render.h"
#include "Buffers.h"

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
	m_drawList.clear();
	delete vsSrc;
	delete fsSrc;
}

void Render::buildTriangle(float* vertex,Texture* texture)
{

	unsigned int indices[3] = { 0, 1, 2 };

	/* Allocate brut memory on GPU */ 
	Buffers* buf = new Buffers();
	buf->storeData(vertex, 21 * sizeof(float));
	Buffers* buf2 = new Buffers();
	buf2->storeData(indices, 3 * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf->GetBuffer(), 0, 7 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	vao->MakeVao(2, 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	glVertexArrayElementBuffer(vao->GetVaoBuffer(), buf2->GetBuffer());

	// Compile Vextex Shader
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	auto* ptr = vsSrc->fileContent.c_str();
	glShaderSource(vs, 1, &ptr, nullptr);
	glCompileShader(vs);

	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fragment shader
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	auto* ptr2 = fsSrc->fileContent.c_str();
	glShaderSource(fs, 1, &ptr2, nullptr);
	glCompileShader(fs);

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link program
	unsigned int sp = glCreateProgram();
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);

	// Check program
	glGetProgramiv(sp, GL_LINK_STATUS, &Result);
	glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(sp, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	std::vector<Buffers*> *test = new std::vector<Buffers*>;
	test->push_back(buf);
	test->push_back(buf2);
	m_drawList.push_back(new DataShape(vao, sp, vs, fs, 3, test,texture));
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

	// Compile Vextex Shader
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	auto* ptr = vsSrc->fileContent.c_str();
	glShaderSource(vs, 1, &ptr, nullptr);
	glCompileShader(vs);

	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fragment shader
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	auto* ptr2 = fsSrc->fileContent.c_str();
	glShaderSource(fs, 1, &ptr2, nullptr);
	glCompileShader(fs);

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link program
	unsigned int sp = glCreateProgram();
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);

	// Check program
	glGetProgramiv(sp, GL_LINK_STATUS, &Result);
	glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(sp, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	// buffer

	Buffers* buf = new Buffers(1);
	Vao* vao = new Vao();

	glBindVertexArray(vao->GetVaoBuffer());
	buf->bind();


	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // asd

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);

	std::vector<Buffers*>* test = new std::vector<Buffers*>;
	test->push_back(buf);

	//m_drawList.push_back(new DataShape(vao, sp, vs, fs, vertices.size(), test));
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

	glVertexArrayElementBuffer(vao->GetVaoBuffer(), buf2->GetBuffer());

	// Compile Vextex Shader
	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	auto* ptr = vsSrc->fileContent.c_str();
	glShaderSource(vs, 1, &ptr, nullptr);
	glCompileShader(vs);

	GLint Result = GL_FALSE;
	int InfoLogLength = 0;

	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(vs, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile fragment shader
	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	auto* ptr2 = fsSrc->fileContent.c_str();
	glShaderSource(fs, 1, &ptr2, nullptr);
	glCompileShader(fs);

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(fs, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link program
	unsigned int sp = glCreateProgram();
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);

	// Check program
	glGetProgramiv(sp, GL_LINK_STATUS, &Result);
	glGetProgramiv(sp, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(sp, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	std::vector<Buffers*>* test = new std::vector<Buffers*>;
	test->push_back(buf);
	test->push_back(buf2);

	//m_drawList.push_back(new DataShape(vao, sp, vs, fs, 6, test));
}

void Render::setShaders()
{

	vsSrc = new File("..\\white_engine_core\\Shaders\\vsSrc.txt");

	fsSrc = new File("..\\white_engine_core\\Shaders\\fsSrc.txt");
}


void Render::drawTriangle()
{
	for (DataShape* shapeToRender : m_drawList)
	{
			glBindTexture(GL_TEXTURE_2D, shapeToRender->texture->texture);
			glBindVertexArray(shapeToRender->shapeVertices->GetVaoBuffer());
			glUseProgram(shapeToRender->progamId);
			glDrawElements(GL_TRIANGLES, shapeToRender->count, GL_UNSIGNED_INT, nullptr);
			glUseProgram(0);
			glBindVertexArray(0);
			delete shapeToRender;
	}
	m_drawList.clear();

}



void Render::drawCircle()
{
	for (DataShape* shapeToRender : m_drawList)
	{
		glBindVertexArray(shapeToRender->shapeVertices->GetVaoBuffer());
		glUseProgram(shapeToRender->progamId);
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
