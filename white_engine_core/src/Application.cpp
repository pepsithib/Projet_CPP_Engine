#include "Application.h"
#include <stdexcept>
#include <vector>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"
#include "Render.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "../Flipper.h"
#include "../Parse.h"

void Application::run()
{
	// On crée un objet Flipper
	Flipper flipper(10.5f, 20.0f, 45.0f);

	// Sérialisation en JSON
	json serializedFlipper = JSONParser::serializeFlipper(flipper);

	// Affichage dans la console
	std::cout << "Serialized JSON:\n" << serializedFlipper.dump(4) << std::endl;

	// Écriture dans un fichier
	std::ofstream file("flipper.json");
	file << serializedFlipper.dump(4);
	file.close();

	// Lecture du fichier
	std::ifstream fileRead("flipper.json");
	json jsonRead;
	fileRead >> jsonRead;
	fileRead.close();

	// Désérialisation de notre objet Flipper
	Flipper flipperDeserialized = JSONParser::deserializeFlipper(jsonRead);

	// Affichage des données désérialisées
	std::cout << "\nDeserialized Flipper Data:\n"
		<< "Position X: " << flipperDeserialized.getPositionX() << ", "
		<< "Position Y: " << flipperDeserialized.getPositionY() << ", "
		<< "Rotation: " << flipperDeserialized.getRotation() << std::endl;

	//FIn test serialisation

	File* vsSrc = new File("..\\white_engine_core\\Shaders\\vsSrc.txt");

	File* fsSrc = new File("..\\white_engine_core\\Shaders\\fsSrc.txt");
	
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

	Render* renderer = Render::getInstance();
	renderer->buildRectangle(vsSrc, fsSrc, 0, 0);

	do
	{
		glfwPollEvents();

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer->drawTriangle();

		glfwSwapBuffers(window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	//glDeleteProgram(sp);
	//glDeleteShader(fs);
	//glDeleteShader(vs);
	//glDeleteBuffers(2, buffers);
	//buf.deleteBuffer();
	//buf2.deleteBuffer();
	delete vsSrc;
	delete fsSrc;

	glfwDestroyWindow(window);
	glfwTerminate();
}
