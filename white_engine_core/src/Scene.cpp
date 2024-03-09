#include "Scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameObject/GameObject.h"
#include "Component/RenderComponent.h"
#include "Component/TransformComponent.h"
#include <imgui.h>
#include <glm/ext/vector_float2.hpp>

Scene::Scene() {}

Scene::~Scene() 
{
    for (int i = 0; i < objects.size(); i++)
    {
        delete objects[i];
    }
}

void Scene::AddEntity(GameObject* object) {
    objects.push_back(object);
}

void Scene::RemoveEntity(GameObject* object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}


void Scene::UpdateScene(float deltaTime) {
    // Mettre à jour chaque GameObject dans la scène
    for (GameObject* gameObject : objects) {
        gameObject->Update(deltaTime);
    }
}

void Scene::RenderObjects(GLFWwindow* window) {
    for (GameObject* object : objects) {
        object->GetComponent<RenderComponent>()->Draw(window);
    }
}

void Scene::DrawDebug()
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
							objects.erase(objects.begin() + i);
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
						GameObject* newGameObject = new GameObject(name, Triangle);
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

