#include "Application.h"
#include <stdexcept>
#include <vector>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"
#include "Render.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GameObject.h>
#include <RenderComponent.h>
#include "../Flipper.h"
#include "../Parse.h"

void Application::run()
{
	// On crée un objet Flipper
	//Flipper flipper(10.5f, 20.0f, 45.0f);

	// Sérialisation en JSON
	//json serializedFlipper = JSONParser::serializeFlipper(flipper);

	// Affichage dans la console
	//std::cout << "Serialized JSON:\n" << serializedFlipper.dump(4) << std::endl;

	// Écriture dans un fichier
	//std::ofstream file("flipper.json");
	//file << serializedFlipper.dump(4);
	//file.close();

	// Lecture du fichier
	//std::ifstream fileRead("flipper.json");
	//json jsonRead;
	//fileRead >> jsonRead;
	//fileRead.close();

	// Désérialisation de notre objet Flipper
	//Flipper flipperDeserialized = JSONParser::deserializeFlipper(jsonRead);

	// Affichage des données désérialisées
	//std::cout << "\nDeserialized Flipper Data:\n"
	//	<< "Position X: " << flipperDeserialized.getPositionX() << ", "
	//	<< "Position Y: " << flipperDeserialized.getPositionY() << ", "
	//	<< "Rotation: " << flipperDeserialized.getRotation() << std::endl;

	//FIn test serialisation
	
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

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
	ImGui_ImplOpenGL3_Init("#version 460");

	GameObject go = GameObject("",{},Triangle);
	Render* renderer = Render::getInstance();
	renderer->setShaders();
	go.GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	do
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		go.Update(0.0f);

		renderer->drawTriangle();
		DrawImgui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);



	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::DrawImgui()
{
	if (ImGui::Begin("Global"))
	{
		if (ImGui::BeginTabBar("Tabs"))
		{
			if (ImGui::BeginTabItem("Edit"))
			{
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}

