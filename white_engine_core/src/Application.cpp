#include "Application.h"
#include <stdexcept>
#include "Buffers.h"
#include "Vao.h"
#include "File.h"
#include "Render.h"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include "RenderComponent.h"
#include "../Flipper.h"
#include "../Parse.h"
#include "TransformComponent.h"
#include <glm/trigonometric.hpp>
#include "GameObject.h"
#include "Render.h"

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

	GameObject* go = new GameObject("Castor",{},Triangle);
	Render* renderer = Render::getInstance();
	renderer->setShaders();
	go->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* go2 = new GameObject("Pollux", {}, Triangle);
	go2->GetComponent<TransformComponent>()->SetWorldPosition({ 0.5, 0.5 });
	go2->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	std::vector<GameObject*> list = { go, go2 };

	do
	{
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (GameObject* i : list)
		{
			i->Update(0.0f);
		}

		renderer->drawTriangle();
#ifdef _QA
		DrawImgui(list);
#endif

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	for (int i = 0; i < list.size(); i++)
	{
		delete list[i];
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();


	glfwDestroyWindow(window);
	glfwTerminate();
}

void Application::DrawImgui(std::vector<GameObject*> &objects)
{ 
	/* Temporary variable to get value througth fields */


	if (ImGui::Begin("Global"))
	{
		if (ImGui::BeginTabBar("Tabs"))
		{
#ifdef _DEBUG
			/* Editor section : use to modified a gameObject transform */
			if (ImGui::BeginTabItem("Editor"))
			{
				for (int i = 0; i < objects.size(); i++)
				{
					if (ImGui::TreeNode(objects[i]->GetFriendlyName().c_str()))
					{
						glm::vec2 position = objects[i]->GetComponent<TransformComponent>()->GetWorldPosition();
						float rotate = objects[i]->GetComponent<TransformComponent>()->GetRotation();
						glm::vec2 scale = objects[i]->GetComponent<TransformComponent>()->GetScale();
						char text[200] = "../white_engine_core/Texture/container.jpg";

						/* Modified Position */
						ImGui::InputFloat2("Position", &position.x);
						objects[i]->GetComponent<TransformComponent>()->SetWorldPosition(position);

						/* Modified Rotate */
						ImGui::InputFloat("Rotate", &rotate);
						objects[i]->GetComponent<TransformComponent>()->SetRotation(glm::radians(rotate));

						/* Modified Scale */
						ImGui::InputFloat2("Scale", &scale.x);
						objects[i]->GetComponent<TransformComponent>()->SetScale(scale);

						//ImGui::InputText("Texture", text, IM_ARRAYSIZE(text));
						//if (ImGui::Button("Change Texture"))
						//{
						//	objects[i]ect->GetComponent<RenderComponent>()->setTexture(text);
						//}

						/* Delete this gameObject */
						if (ImGui::Button("Delete Object"))
						{
							delete objects[i];
							objects.erase(objects.begin()+i);
						}

						ImGui::TreePop();
					}
					ImGui::Separator();
				}

				/* Section to add a new game object to the scene */
				if (ImGui::TreeNode("Add New gameObject"))
				{
					/* Enter the name of the object */
					static char name[30] = "default";
					ImGui::InputText("Name", name, IM_ARRAYSIZE(name));

					/* Enter the position of the object */
					static glm::vec2 position = { 0,0 };
					ImGui::InputFloat2("Position", &position.x);

					if (ImGui::Button("Add Object"))
					{
						GameObject* newGameObject = new GameObject(name, {}, Triangle);
						newGameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);
						newGameObject->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
						objects.push_back(newGameObject);
					}
					ImGui::TreePop();
				}
				
				ImGui::EndTabItem();
			}
#endif
			/* Info section : use to display debug info */
			if (ImGui::BeginTabItem("Debug Info"))
			{
				for (int i = 0; i < objects.size(); i++)
				{
					char pos[DEBUG_INFO_SIZE];
					char rot[DEBUG_INFO_SIZE];
					char sca[DEBUG_INFO_SIZE];

					snprintf(pos, DEBUG_INFO_SIZE, "Position : %3.2f, %3.2f", objects[i]->GetComponent<TransformComponent>()->GetWorldPosition().x, objects[i]->GetComponent<TransformComponent>()->GetWorldPosition().y);
					snprintf(rot, DEBUG_INFO_SIZE, "Rotation : %3.2f", objects[i]->GetComponent<TransformComponent>()->GetRotation());
					snprintf(sca, DEBUG_INFO_SIZE, "Scale : %3.2f, %3.2f", objects[i]->GetComponent<TransformComponent>()->GetScale().x, objects[i]->GetComponent<TransformComponent>()->GetScale().y);

					if (ImGui::TreeNode(objects[i]->GetFriendlyName().c_str()))
					{
						ImGui::Text(pos);
						ImGui::Text(rot);
						ImGui::Text(sca);
						ImGui::TreePop();
					}
				}
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}
	ImGui::End();
}

