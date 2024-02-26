#include "Application.h"
#include <stdexcept>
#include <vector>

#include "File.h"
#include "Render/Render.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <GameObject/GameObject.h>
#include <Component/RenderComponent.h>
#include <Component/TransformComponent.h>


#include <glm/vec2.hpp>
#include <glm/trigonometric.hpp>
#include <Component/PhysicComponent.h>
#include <Component/ColliderComponent.h>

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

	Render* renderer = Render::getInstance();
	renderer->setShaders();

	GameObject go = GameObject("",Rectangle);
	GameObject go2 = GameObject("", Rectangle);
	
	go.GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");
	go2.GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/dolphin.jpg");
	go2.GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(-1.0, -0.5));
	go2.GetComponent<TransformComponent>()->SetScale(glm::vec2(10.0, 1.0));
	float rot = 0;
	float x = 0;
	float y = 0;
	int w, h;

	go.AddComponent<PhysicComponent>();
	go.AddComponent<ColliderComponent>();
	go2.AddComponent<ColliderComponent>();
	go.GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(0.0, 0.0));
	go.GetComponent<PhysicComponent>()->AddImpulse(glm::vec2(0.0, 3.0));
	glfwGetWindowSize(window, &w, &h);
	glfwSetTime(0.0);
	do
	{
		double dTime = glfwGetTime();
		glfwSetTime(0.0);
		glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		y = go.GetComponent<TransformComponent>()->GetWorldPosition().y;
		if (y < -(float(w) / float(h)) - 0.2) {
			y = (float(w) / float(h)) + 0.2;
		}

		go.GetComponent<PhysicComponent>()->AddForce(glm::vec2(0.0, 8.0));
		go.GetComponent<TransformComponent>()->SetRotation(glm::radians(rot));
		go.GetComponent<TransformComponent>()->SetWorldPosition(glm::vec2(go.GetComponent<TransformComponent>()->GetWorldPosition().x,y));
		go.Update(dTime);
		go2.Update(dTime);
		std::cout << go.GetComponent<ColliderComponent>()->CollideWith(go2.GetComponent<ColliderComponent>()) << std::endl;
		go.GetComponent<RenderComponent>()->Draw(window);
		go2.GetComponent<RenderComponent>()->Draw(window);
		DrawImgui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);

	//glDeleteProgram(sp);
	//glDeleteShader(fs);
	//glDeleteShader(vs);
	//glDeleteBuffers(2, buffers);
	//buf.deleteBuffer();
	//buf2.deleteBuffer();

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
