#include <iostream>
#include <stdexcept>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

float vertices[15] = {
	 0.0f,  0.5f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f
};

unsigned int indices[3] = { 0, 1, 2 };

const char* vsSrc = R"(#version 460 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
void main()
{
	gl_Position = vec4(aPos, 0.0, 1.0);
	vColor = aColor;
})";

const char* fsSrc = R"(#version 460 core
in vec3 vColor;
layout(location = 0) out vec4 oFragColor;
void main()
{
	oFragColor = vec4(vColor, 1.0);
})";

// Les sommets. Trois floats consécutifs donnent un sommet 3D ; trois sommets consécutifs donnent un triangle. 
// Un cube possède six faces avec deux triangles pour chaque, donc cela fait 6*2=12 triangles et 12*3=36 sommets 
static const GLfloat g_vertex_buffer_data[] = { 
    -1.0f,-1.0f,-1.0f, // triangle 1 : début
    -1.0f,-1.0f, 1.0f, 
    -1.0f, 1.0f, 1.0f, // triangle 1 : fin 
    1.0f, 1.0f,-1.0f, // triangle 2 : début 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f,-1.0f, // triangle 2 : fin 
    1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f, 1.0f, 
    -1.0f,-1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    -1.0f,-1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f,-1.0f, 
    1.0f,-1.0f,-1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    1.0f, 1.0f,-1.0f, 
    -1.0f, 1.0f,-1.0f, 
    1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f,-1.0f, 
    -1.0f, 1.0f, 1.0f, 
    1.0f, 1.0f, 1.0f, 
    -1.0f, 1.0f, 1.0f, 
    1.0f,-1.0f, 1.0f 
};
// Une couleur pour chaque sommet. Elles ont été générées aléatoirement. 
// Source tuto openGL afficher un cube
static const GLfloat g_color_buffer_data[] = {
	0.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  0.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	0.597f,  0.770f,  0.761f,
	0.559f,  0.436f,  0.730f,
	0.359f,  0.583f,  0.152f,
	0.483f,  0.596f,  0.789f,
	0.559f,  0.861f,  0.639f,
	0.195f,  0.548f,  0.859f,
	0.014f,  0.184f,  0.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  0.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  0.513f,  0.064f,
	0.945f,  0.719f,  0.592f,
	0.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  0.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  0.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  0.587f,  0.040f,
	0.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};


int main(int argc, char** argv)
{
	//// Affiche le triangle ! 
	//glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // 12*3 indices démarrant à 0 -> 12 triangles -> 6 carrés
	//// Source cube tuto p=opengl
	//GLuint colorbuffer;
	//glGenBuffers(1, &colorbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	//// second tampon d'attributs : couleurs 
	//// Configuration
	//glEnableVertexAttribArray(1);
	//glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	//glVertexAttribPointer(
	//	1,                                // attribut. Aucune raison particulière pour 1, mais cela doit correspondre au « layout » du shader 
	//	3,                                // taille 
	//	GL_FLOAT,                         // type 
	//	GL_FALSE,                         // normalisé ? 
	//	0,                                // nombre d'octets séparant deux sommets dans le tampon 
	//	(void*)0                          // décalage du tableau de tampons 
	//);



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

	GLFWwindow* window = glfwCreateWindow(800, 480, "Ynov - Engine test", nullptr, nullptr);
	if (!window)
		throw std::runtime_error("Unable to initialize GLFW");

	glfwMakeContextCurrent(window);

	glewExperimental = true;
	glewInit();

	unsigned int buffers[2];
	glCreateBuffers(2, buffers);
	glNamedBufferStorage(buffers[0], 15 * sizeof(float), vertices, 0);
	glNamedBufferStorage(buffers[1], 3 * sizeof(unsigned int), indices, 0);

	unsigned int vao;
	glCreateVertexArrays(1, &vao);
	glVertexArrayVertexBuffer(vao, 0, buffers[0], 0, 5 * sizeof(float));
	glEnableVertexArrayAttrib(vao, 0);
	glVertexArrayAttribBinding(vao, 0, 0);
	glVertexArrayAttribFormat(vao, 0, 2, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(vao, 1);
	glVertexArrayAttribBinding(vao, 1, 0);
	glVertexArrayAttribFormat(vao, 1, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(float));
	glVertexArrayElementBuffer(vao, buffers[1]);

	unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vsSrc, nullptr);
	glCompileShader(vs);

	unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fsSrc, nullptr);
	glCompileShader(fs);

	unsigned int sp = glCreateProgram();
	glAttachShader(sp, vs);
	glAttachShader(sp, fs);
	glLinkProgram(sp);

	do
	{
		glfwPollEvents();

		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(vao);
		glUseProgram(sp);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
		glUseProgram(0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
	} while (!glfwWindowShouldClose(window));

	glDeleteProgram(sp);
	glDeleteShader(fs);
	glDeleteShader(vs);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(2, buffers);

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
