#include "Application.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <stdexcept>
#include <vector>

#include "File.h"
#include "Render/Render.h"


#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GameObject/GameObject.h>
#include <Component/RenderComponent.h>
#include <Component/TransformComponent.h>
#include <Scene.h>
#include <SceneManager.h>

#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <Component/PhysicComponent.h>
#include <Component/ColliderComponent.h>

#include "../Parse.h"
#include <glm/trigonometric.hpp>
#include "../InputManager.h"
#include "../EventSystem.h"



void Application::init(Scene* scene)
{

	GameObject* l_side = new GameObject("l_side",Shape::Rectangle);
	GameObject* r_side = new GameObject("r_side", Shape::Rectangle);
	GameObject* t_side = new GameObject("t_side", Shape::Rectangle);

	scene->AddEntity(l_side);
	scene->AddEntity(r_side);
	scene->AddEntity(t_side);

	l_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-0.65, 0));
	r_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.65, 0));
	t_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0, .95));

	l_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 10.0));
	r_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 10.0));
	t_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(7, .5));

	l_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	t_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* l_funnel = new GameObject("l_funnel", Shape::Rectangle);
	GameObject* r_funnel = new GameObject("r_funnel", Shape::Rectangle);

	scene->AddEntity(l_funnel);
	scene->AddEntity(r_funnel);

	l_funnel->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-0.6, -.9));
	r_funnel->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.5, -.9));

	l_funnel->GetComponent<TransformComponent>()->SetScale(glm::vec2(2.5, 2.5));
	r_funnel->GetComponent<TransformComponent>()->SetScale(glm::vec2(2.5, 2.5));

	l_funnel->GetComponent<TransformComponent>()->SetRotation(glm::radians(45.0));
	r_funnel->GetComponent<TransformComponent>()->SetRotation(glm::radians(-45.0));

	l_funnel->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_funnel->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* ball_launcher = new GameObject("ball_launcher", Shape::Rectangle);

	scene->AddEntity(ball_launcher);

	ball_launcher->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.5, -.3));

	ball_launcher->GetComponent<TransformComponent>()->SetScale(glm::vec2(.2,4.0));

	ball_launcher->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* l_Paddle = new GameObject("l_paddle", Shape::Rectangle);
	GameObject* r_Paddle = new GameObject("r_paddle", Shape::Rectangle);
	GameObject* Bumper1 = new GameObject("Bumper1", Shape::Circle);
	GameObject* Ball = new GameObject("Ball", Shape::Circle);

	scene->AddEntity(l_Paddle);
	scene->AddEntity(r_Paddle);
	scene->AddEntity(Bumper1);
	scene->AddEntity(Ball);

	l_Paddle->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-.3, -.5));
	r_Paddle->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.2, -.5));

	l_Paddle->GetComponent<TransformComponent>()->SetScale(glm::vec2(1.5, .2));
	r_Paddle->GetComponent<TransformComponent>()->SetScale(glm::vec2(1.5, 0.2));

	l_Paddle->GetComponent<TransformComponent>()->SetPivot(glm::vec2(-.1, 0));
	r_Paddle->GetComponent<TransformComponent>()->SetPivot(glm::vec2(.1, 0));

	l_Paddle->GetComponent<TransformComponent>()->SetRotation(glm::radians(45.f));
	r_Paddle->GetComponent<TransformComponent>()->SetRotation(glm::radians(-45.f));

	l_Paddle->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_Paddle->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	l_Paddle->AddTag("Paddle");
	r_Paddle->AddTag("Paddle");

	Bumper1->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.2, .2));

	Bumper1->AddTag("Bumper");

	Ball->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/Ball.jpg");
	Ball->GetComponent<TransformComponent>()->SetScale(glm::vec2(0.5,0.5));
	Ball->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.2, 0));
	for (GameObject* object : scene->GetObjects()) {
		object->AddComponent<PhysicComponent>();
		object->AddComponent<ColliderComponent>();
		object->GetComponent<PhysicComponent>()->setStatic();
		object->GetComponent<ColliderComponent>()->setStatic(); // set all object to be static
	}
	Ball->GetComponent<PhysicComponent>()->setStatic();
	Ball->GetComponent<ColliderComponent>()->setStatic(); // reset the ball to not static
}

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
	int width = 550;
	int height = 800;
	GLFWwindow* window = glfwCreateWindow(width,height , "White Engine", nullptr, nullptr);
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

	Render* renderer = Render::getInstance();
	renderer->setShaders();

	SceneManager* sceneList = new SceneManager();
	Scene* scene = new Scene();

	init(scene);

	EventSystem& eventSystem = EventSystem::getInstance();
	InputManager& inputManager = InputManager::getInstance(window);

	eventSystem.AddEventListener("LeftArrowPressed", [&]() 
	{
		std::cout << "Flèche gauche enfoncée" << std::endl;
	});

	eventSystem.AddEventListener("RightArrowPressed", [&]() 
	{
		std::cout << "Flèche droite enfoncée" << std::endl;
	});

	eventSystem.AddEventListener("SpaceBarPressed", [&]() 
	{
		std::cout << "Barre d'espace enfoncée" << std::endl;
	});

	int w, h;
	float dTime = 0;

	glfwGetWindowSize(window, &w, &h);
	do
	{
		auto start = std::chrono::utc_clock::now();
		glfwPollEvents();

		//test
		
		// Mise à jour des inputs
		inputManager.updateInputState();

		// Récupération de l'état des inputs
		InputState inputState = inputManager.getInputState();

		// Traitement des inputs
		if (inputState.leftArrowPressed) {
			// Action à effectuer lorsque la touche flèche gauche est enfoncée
			std::cout << "Flèche gauche enfoncée" << std::endl;
		}
		if (inputState.rightArrowPressed) {
			// Action à effectuer lorsque la touche flèche droite est enfoncée
			std::cout << "Flèche droite enfoncée" << std::endl;
		}
		if (inputState.spaceBarPressed) {
			// Action à effectuer lorsque la barre d'espace est enfoncée
			std::cout << "Barre d'espace enfoncée" << std::endl;
		}


		// fiun test

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (GameObject* object : scene->GetObjects()) {
			for (GameObject* object2 : scene->GetObjects()) { //double boucle pour tester chaque object avec chaque object
				if (object != object2) { // si l'objet et different de lui meme, sinon on skip
					if (object->GetComponent<ColliderComponent>()->CollideWith(object2->GetComponent<ColliderComponent>())) { // on test les collisions
						if (object->GetComponent<PhysicComponent>()) { // si l'object contient un physic
							std::cout << object2->GetFriendlyName() << std::endl;
							glm::vec2 oVel = object->GetComponent<PhysicComponent>()->getVelocity();
							object->GetComponent<PhysicComponent>()->setVelocity(glm::vec2(0.0, 0.0));
							if (object2->GetFriendlyName() == "l_paddle" || object2->GetFriendlyName() == "r_paddle") {
								object->GetComponent<PhysicComponent>()->AddImpulse(glm::reflect(oVel, object->GetComponent<ColliderComponent>()->HitNormal));
								
							}else if(object2->GetFriendlyName() == ""){}
							else {
								object->GetComponent<PhysicComponent>()->AddImpulse(glm::reflect(oVel/glm::vec2(2.0), object->GetComponent<ColliderComponent>()->HitNormal));
							}
							
						}
					}
				}
			}
		}


		/* Update all the element in the scene */
		scene->UpdateScene(dTime);

		

		/* Render all the element in the scene */
		scene->RenderObjects(window);

#ifdef _QA
		scene->DrawDebug();
#endif

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


		auto end = std::chrono::utc_clock::now();
		dTime = std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete sceneList;
	delete scene;

	glfwDestroyWindow(window);
	glfwTerminate();
}

