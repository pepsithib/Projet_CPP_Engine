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
#include <Component/SoundManager.h>
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



void Application::init(Scene* scene,InputManager* IM,EventSystem* ES)
{

	GameObject* l_side = new GameObject("l_side",Shape::Rectangle);
	GameObject* r_side = new GameObject("r_side", Shape::Rectangle);
	GameObject* t_side = new GameObject("t_side", Shape::Rectangle);
	GameObject* t1_side = new GameObject("t1_side", Shape::Rectangle);
	GameObject* t2_side = new GameObject("t2_side", Shape::Rectangle);

	scene->AddEntity(l_side);
	scene->AddEntity(r_side);
	scene->AddEntity(t_side);
	scene->AddEntity(t1_side);
	scene->AddEntity(t2_side);

	l_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-0.65, 0));
	r_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.65, 0));
	t_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0, .95));
	t1_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.55, .5));
	t2_side->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-0.55, .5));

	l_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 10.0));
	r_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 10.0));
	t_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(7, 0.5));
	t1_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 5));
	t2_side->GetComponent<TransformComponent>()->SetScale(glm::vec2(.5, 5));

	t1_side->GetComponent<TransformComponent>()->SetRotation(glm::radians(-20.f));
	t2_side->GetComponent<TransformComponent>()->SetRotation(glm::radians(20.f));

	l_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	t_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	t1_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	t2_side->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* l_funnel = new GameObject("l_funnel", Shape::Rectangle);
	GameObject* r_funnel = new GameObject("r_funnel", Shape::Rectangle);

	scene->AddEntity(l_funnel);
	scene->AddEntity(r_funnel);

	l_funnel->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-0.6, -.9));
	r_funnel->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.5, -.9));

	l_funnel->GetComponent<TransformComponent>()->SetScale(glm::vec2(2.5, 2.5));
	r_funnel->GetComponent<TransformComponent>()->SetScale(glm::vec2(2.5, 2.5));

	l_funnel->GetComponent<TransformComponent>()->SetRotation(glm::radians(10.f));
	r_funnel->GetComponent<TransformComponent>()->SetRotation(glm::radians(-10.f));

	l_funnel->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_funnel->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	GameObject* ball_launcher = new GameObject("ball_launcher", Shape::Rectangle);
	GameObject* ball_launcher_b = new GameObject("ball_launcher_b", Shape::Rectangle);
	scene->AddEntity(ball_launcher);
	scene->AddEntity(ball_launcher_b);

	ball_launcher->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.45, -.3));
	ball_launcher_b->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.65, -.64));

	ball_launcher->GetComponent<TransformComponent>()->SetScale(glm::vec2(.2,4.0));
	ball_launcher_b->GetComponent<TransformComponent>()->SetScale(glm::vec2(2.0, 0.2));

	ball_launcher->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	ball_launcher_b->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	GameObject* l_Paddle = new GameObject("l_paddle", Shape::Rectangle);
	GameObject* r_Paddle = new GameObject("r_paddle", Shape::Rectangle);
	GameObject* Bumper1 = new GameObject("Bumper1", Shape::Circle);
	GameObject* Ball = new GameObject("Ball", Shape::Circle);

	scene->AddEntity(l_Paddle);
	scene->AddEntity(r_Paddle);
	scene->AddEntity(Bumper1);
	scene->AddEntity(Ball);

	l_Paddle->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-.230, -.730));
	r_Paddle->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.130, -.730));

	l_Paddle->GetComponent<TransformComponent>()->SetScale(glm::vec2(1.2, .2));
	r_Paddle->GetComponent<TransformComponent>()->SetScale(glm::vec2(1.2, 0.2));

	l_Paddle->GetComponent<TransformComponent>()->SetPivot(glm::vec2(-.1, 0));
	r_Paddle->GetComponent<TransformComponent>()->SetPivot(glm::vec2(.1, 0));

	l_Paddle->GetComponent<TransformComponent>()->SetRotation(glm::radians(45.f));
	r_Paddle->GetComponent<TransformComponent>()->SetRotation(glm::radians(-45.f));

	l_Paddle->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	r_Paddle->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

	l_Paddle->AddTag("Paddle");
	r_Paddle->AddTag("Paddle");

	l_Paddle->AddComponent<SoundManager>();
	l_Paddle->GetComponent<SoundManager>()->addSound("../white_engine_core/Sounds/PaddleSound.wav", "Clonk");

	r_Paddle->AddComponent<SoundManager>();
	r_Paddle->GetComponent<SoundManager>()->addSound("../white_engine_core/Sounds/PaddleSound.wav", "Clonk");

	Bumper1->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(.2, .2));
	Bumper1->AddComponent<SoundManager>();
	Bumper1->GetComponent<SoundManager>()->addSound("../white_engine_core/Sounds/ding.wav", "Ding");

	Bumper1->AddTag("Bumper");
	Ball->AddTag("Ball");
	Ball->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/Ball.jpg");
	Ball->GetComponent<TransformComponent>()->SetScale(glm::vec2(0.5,0.5));
	Ball->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.53, -0.5));
	for (GameObject* object : scene->GetObjects()) {
		object->AddComponent<PhysicComponent>();
		object->AddComponent<ColliderComponent>();
		object->GetComponent<PhysicComponent>()->setStatic();
		object->GetComponent<ColliderComponent>()->setStatic(); // set all object to be static
	}
	Ball->GetComponent<PhysicComponent>()->setStatic();
	Ball->GetComponent<ColliderComponent>()->setStatic(); // reset the ball to not static
	
	IM->AddInputToWatch(InputKey::Q);
	IM->AddInputToWatch(InputKey::M);
	IM->AddInputToWatch(InputKey::LEFT);
	IM->AddInputToWatch(InputKey::RIGHT);
	IM->AddInputToWatch(InputKey::SPACE);
	IM->AddInputToWatch(InputKey::S);
	IM->AddInputToWatch(InputKey::L);
}

void Application::run()
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

	sceneList->addScene(scene);
	


	EventSystem* eventSystem = EventSystem::getInstance();
	InputManager* inputManager = InputManager::getInstance(window);

	init(scene,inputManager,eventSystem);


	JSONParser parser = JSONParser();

	bool can_launch_ball = true;

	eventSystem->AddEventListener("l_paddle_rotate", [&]() 
	{

			GameObject* paddle = scene->GetObject("l_paddle");
			if (paddle->GetComponent<TransformComponent>()->GetRotation() > glm::radians(-25.f)) {
				paddle->GetComponent<TransformComponent>()->SetRotation(paddle->GetComponent<TransformComponent>()->GetRotation()+glm::radians(-1.f));
			}
			
	});
	eventSystem->AddEventListener("l_paddle_reset", [&]()
		{
			GameObject* paddle = scene->GetObject("l_paddle");
			if (paddle->GetComponent<TransformComponent>()->GetRotation() < glm::radians(25.f)) {
				paddle->GetComponent<TransformComponent>()->SetRotation(paddle->GetComponent<TransformComponent>()->GetRotation() + glm::radians(1.f));
				paddle->GetComponent<SoundManager>()->playSound("Clonk", false);
			}
			
		});

	eventSystem->AddEventListener("r_paddle_rotate", [&]()
		{

			GameObject* paddle = scene->GetObject("r_paddle");
			if (paddle->GetComponent<TransformComponent>()->GetRotation() < glm::radians(25.f)) {
				paddle->GetComponent<TransformComponent>()->SetRotation(paddle->GetComponent<TransformComponent>()->GetRotation() + glm::radians(1.f));
				paddle->GetComponent<SoundManager>()->playSound("Clonk", false);
			}

		});
	eventSystem->AddEventListener("r_paddle_reset", [&]()
		{
			GameObject* paddle = scene->GetObject("r_paddle");
			if (paddle->GetComponent<TransformComponent>()->GetRotation() > glm::radians(-25.f)) {
				paddle->GetComponent<TransformComponent>()->SetRotation(paddle->GetComponent<TransformComponent>()->GetRotation() + glm::radians(-1.f));
			}

		});
	eventSystem->AddEventListener("launch_ball", [&]()
		{
			GameObject* ball = scene->GetObject("Ball");
			if (can_launch_ball) {
				ball->GetComponent<PhysicComponent>()->AddImpulse(glm::vec2(0.0, 10.0));
				can_launch_ball = false;
			}

		});

	int w, h;
	float dTime = 0;
	bool pressedOnce = false;

	bool paddle_l_launch = false;
	bool paddle_r_launch = false;


	int score = 0;

	glfwGetWindowSize(window, &w, &h);
	do
	{
		auto start = std::chrono::utc_clock::now();
		glfwPollEvents();
		
		/* Input Update */
		inputManager->updateInputState();

		if (inputManager->CheckInput(InputKey::Q) || inputManager->CheckInput(InputKey::LEFT)) {
			eventSystem->TriggerEvent("l_paddle_rotate");
			paddle_l_launch = true;
		}
		else {
			eventSystem->TriggerEvent("l_paddle_reset");
			paddle_l_launch = false;
		}
		if (inputManager->CheckInput(InputKey::M) || inputManager->CheckInput(InputKey::RIGHT)) {
			eventSystem->TriggerEvent("r_paddle_rotate");
			paddle_r_launch = true;
		}
		else {
			eventSystem->TriggerEvent("r_paddle_reset");
			paddle_r_launch = false;
		}
		if (inputManager->CheckInput(InputKey::SPACE)) {
			eventSystem->TriggerEvent("launch_ball");
			
		}if (inputManager->CheckInput(InputKey::S)) {
			saveGame(scene, parser);
		}if (inputManager->CheckInput(InputKey::L)) {
			if (std::filesystem::exists("../white_engine_core/Save/save.json"))
			{
				delete scene;
				scene = new Scene();
				loadGame(*scene, parser);
				sceneList->setScene(0, scene);
				can_launch_ball = true;
			}
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		for (GameObject* object : scene->GetObjects()) {
			for (GameObject* object2 : scene->GetObjects()) { /* Double loop to test collisions beetween each objects */
				if (object != object2) { /* If same object, skip */
					if (object->GetComponent<ColliderComponent>()->CollideWith(object2->GetComponent<ColliderComponent>())) { /* Collision test */
						if (object->GetComponent<PhysicComponent>()) { /* If object as physic */
							std::cout << object2->GetFriendlyName() << std::endl;
							glm::vec2 oVel = object->GetComponent<PhysicComponent>()->getVelocity();
							object->GetComponent<PhysicComponent>()->setVelocity(glm::vec2(0.0, 0.0));
							if (object2->GetFriendlyName() == "l_paddle" && paddle_l_launch) {
								object->GetComponent<PhysicComponent>()->AddImpulse(glm::vec2(oVel.x, 5.0));
								
							}
							else if(object2->GetFriendlyName() == "r_paddle" && paddle_r_launch){
								object->GetComponent<PhysicComponent>()->AddImpulse(glm::vec2(oVel.x, 5.0));
							}
							else if (object2->ContainTag("Bumper")) {
								object->GetComponent<PhysicComponent>()->AddImpulse(glm::vec2(oVel.x,5.0));
								object2->GetComponent<SoundManager>()->playSound("Ding", false);
								score++;
							}
							else {
								if (glm::length(oVel) > 0.1) {
									object->GetComponent<PhysicComponent>()->AddImpulse(glm::reflect(oVel, object->GetComponent<ColliderComponent>()->HitNormal));
								}
								else if (glm::length(oVel) < 0.1) {
									object->GetComponent<PhysicComponent>()->AddForce(glm::vec2(0.0, -GRAVITY));
								}
								
							}
							
						}
					}
				}
			}
			if (object->ContainTag("Ball")) {
				if (object->GetComponent<TransformComponent>()->GetWorldPosition().y < -1) {
					object->GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.53,-0.5));
					object->GetComponent<PhysicComponent>()->setVelocity(glm::vec2(0.0));
					can_launch_ball = true;
				}
			}
		}


		/* Update all the element in the scene */
		scene->UpdateScene(dTime);

		

		/* Render all the element in the scene */
		scene->RenderObjects(window);

#ifdef _QA
		scene->DrawDebug(score);
#endif

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);


		auto end = std::chrono::utc_clock::now();
		dTime = std::chrono::duration<float, std::chrono::seconds::period>(end - start).count();

		pressedOnce = false;

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);


	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	delete sceneList;

	glfwDestroyWindow(window);
	glfwTerminate();
}

void  Application::saveGame(Scene* sceneToSave, JSONParser &parser)
{
	/* Save in json variable */
	json serializedFlipper = parser.serializeFlipper(sceneToSave);

	/* Writing json variable into json file */
	std::ofstream file("../white_engine_core/Save/save.json");
	file << serializedFlipper.dump(4);
	file.close();
}

void Application::loadGame(Scene& sceneToReload, JSONParser &parser)
{
	std::ifstream fileRead("../white_engine_core/Save/save.json");
	json jsonRead = json::parse(fileRead);
	fileRead.close();

	parser.deserializeFlipper(jsonRead, sceneToReload);
}

