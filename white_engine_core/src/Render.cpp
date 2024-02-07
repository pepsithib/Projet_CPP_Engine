#include "Render.h"
#include "Buffers.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
Render::~Render()
{
	for (DataShape* shapeToDelete : m_drawList)
	{
		delete shapeToDelete->shapeVertices;
		glDeleteProgram(shapeToDelete->progamId);
		glDeleteShader(shapeToDelete->fragmentShader);
		glDeleteShader(shapeToDelete->vertexShader);
		delete shapeToDelete;
	}

}

void Render::buildTriangle(File* vsSrc, File* fsSrc)
{
	float vertices[15] = {
	 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
	};

	unsigned int indices[3] = { 0, 1, 2 };

	/* Allocate brut memory on GPU */ 
	Buffers buf;
	buf.storeData(vertices, 15 * sizeof(float));
	Buffers buf2;
	buf2.storeData(indices, 3 * sizeof(unsigned int));

	/* Create the Vao */
	Vao* vao = new Vao(0, buf.GetBuffer(), 0, 5 * sizeof(float));

	vao->MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao->MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));

	glVertexArrayElementBuffer(vao->GetVaoBuffer(), buf2.GetBuffer());

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
	m_drawList.push_back(new DataShape(vao, sp, vs, fs));
}

void Render::buildCircle(float radius, int dotNumbers, File* vsSrc, File* fsSrc)
{
	std::vector<glm::vec3> vertices;
	unsigned int vertexBuffer;
	unsigned int vertexArray;

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
	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);


	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW); // asd

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(0);
}

void Render::buildRectangle(File* vsSrc, File* fsSrc)
{
}

void Render::drawTriangle()
{
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	for (DataShape* shapeToRender : m_drawList)
	{
		glBindVertexArray(shapeToRender->shapeVertices->GetVaoBuffer());
		glUseProgram(shapeToRender->progamId);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);
	}

}
