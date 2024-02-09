
#include <stdexcept>
#include <vector>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>

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
	Application* app = new Application();
	app->run();
	delete app;
}

#ifdef NDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
	return main(0, nullptr);
}
#endif /* NDEBUG */
