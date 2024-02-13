
#include "GL/glew.h"
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"

float vertices[15] = {
	 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[3] = { 0, 1, 2 };

File* vsSrc = new File("..\\white_engine_core\\Shaders\\vsSrc.txt");

File* fsSrc = new File("..\\white_engine_core\\Shaders\\fsSrc.txt");

int main()
{
	glfwInit();

	// Set context as OpenGL 4.6 Core, forward compat, with debug depending on build config
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#ifndef NDEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#else /* !NDEBUG */
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_FALSE);
#endif /* !NDEBUG */
	glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 480, "White Engine", nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Unable to initialize GLFW");

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	// allocation de memoire de donnee brute dans la carte graphique
	Buffers buf;
	buf.storeData(vertices, 15 * sizeof(float));
	Buffers buf2;
	buf2.storeData(indices, 3 * sizeof(unsigned int));

	/* Create the Vao */
	Vao vao(0, buf.GetBuffer(), 0, 5 * sizeof(float));

	vao.MakeVao(0, 0, 2, GL_FLOAT, GL_FALSE, 0);
	vao.MakeVao(1, 0, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));

	glVertexArrayElementBuffer(vao.GetVaoBuffer(), buf2.GetBuffer());

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

	do
	{
		glfwPollEvents();

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao.GetVaoBuffer());
		glUseProgram(sp);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	glDeleteProgram(sp);
	glDeleteShader(fs);
	glDeleteShader(vs);
	//glDeleteBuffers(2, buffers);
	//buf.deleteBuffer();
	//buf2.deleteBuffer();
	delete vsSrc;
	delete fsSrc;

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

#ifdef NDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	return main(0, nullptr);
}
#endif /* NDEBUG */
