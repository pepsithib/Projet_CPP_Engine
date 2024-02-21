//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <stdexcept>
#include <vector>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"
#include "Application.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>


int main()
{
	Application* app = new Application();
	app->run();
	delete app;
}
