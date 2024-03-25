#include "Scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameObject/GameObject.h"
#include "Component/RenderComponent.h"
#include "Component/TransformComponent.h"
#include "Component/ColliderComponent.h"
#include "Component/PhysicComponent.h"
#include "Component/SoundManager.h"
#include <imgui.h>
#include <glm/ext/vector_float2.hpp>
#include <cmath>

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

std::vector<GameObject*> Scene::getObjects()
{
	return objects;
}

void Scene::DrawDebug()
{
	/* Main ImGui window */
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
						float rotate = glm::degrees(objects[i]->GetComponent<TransformComponent>()->GetRotation());
						glm::vec2 scale = objects[i]->GetComponent<TransformComponent>()->GetScale();
						static char text[200] = "../white_engine_core/Texture/container.jpg";

						/* Modifie Position */
						ImGui::InputFloat2("Position", &position.x);
						objects[i]->GetComponent<TransformComponent>()->SetWorldPosition(position);

						/* Modifie Rotate */
						ImGui::InputFloat("Rotate", &rotate);
						objects[i]->GetComponent<TransformComponent>()->SetRotation(glm::radians(rotate));

						/* Modifie Scale */
						ImGui::InputFloat2("Scale", &scale.x);
						objects[i]->GetComponent<TransformComponent>()->SetScale(scale);

						/* Modifie Texture */
						ImGui::InputText("Texture", text, IM_ARRAYSIZE(text));
						if (ImGui::Button("Change Texture"))
						{
							objects[i]->GetComponent<RenderComponent>()->setTexture(text);
						}

						/* Modifie the soundManager if the object has this component */
						if (objects[i]->GetComponent<SoundManager>())
						{
							if (ImGui::TreeNode("SoundManager"))
							{

								ImGui::Text("Add Sound");

								/* Set the path and a name */
								static char soundName[200] = "default";
								if (ImGui::InputText("New Sound name", soundName, IM_ARRAYSIZE(soundName)));
								static char soundPath[200] = { 0 };
								ImGui::InputText("New Sound path", soundPath, IM_ARRAYSIZE(soundPath));

								/* Push the new value */
								if (ImGui::Button("Add Sound"))
								{
									objects[i]->GetComponent<SoundManager>()->addSound(soundPath, soundName);
								}

								ImGui::Text("Delete Sound");

								static char deleteSoundName[200] = { 0 };
								ImGui::InputText("Sound to delete", deleteSoundName, IM_ARRAYSIZE(deleteSoundName));

								/* Remove the sound from this gameObject */
								if (ImGui::Button("Remove Sound"))
								{
									objects[i]->GetComponent<SoundManager>()->deleteSound(deleteSoundName);
								}

								ImGui::Text("Play Sound");

								/* Enter the name of the sound to play */
								static char playSoundName[200] = { 0 };
								ImGui::InputText("Sound to Play", playSoundName, IM_ARRAYSIZE(playSoundName));

								/* Play that sound */
								if (ImGui::Button("Play Sound"))
								{
									objects[i]->GetComponent<SoundManager>()->playSound(playSoundName, false);
								}

								ImGui::TreePop();
							}
						}

						/* Modifie the PhysicComponent if the object has this component */
						if (objects[i]->GetComponent<PhysicComponent>())
						{
							if (ImGui::TreeNode("Physic"))
							{
								/* Get the velocity and acceleration vector */
								glm::vec2 velocity = objects[i]->GetComponent<PhysicComponent>()->getVelocity();
								glm::vec2 acceleration = objects[i]->GetComponent<PhysicComponent>()->getAcceleration();

								/* Modifie Velocity */
								ImGui::InputFloat2("Velocity", &velocity.x);
								objects[i]->GetComponent<PhysicComponent>()->setVelocity(velocity);

								/* Modifie Acceleration */
								ImGui::InputFloat2("Acceleration", &acceleration.x);
								objects[i]->GetComponent<PhysicComponent>()->setAcceleration(acceleration);

								ImGui::TreePop();
							}
						}

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

					/* Decide if the gameObject has a soundManager */
					static bool hasSound = false;
					ImGui::Checkbox("soundManager", &hasSound);

					/* Decide if the gameObject has a Physics */
					static bool hasPhysics = false;
					ImGui::Checkbox("Physics", &hasPhysics);

					if (ImGui::Button("Add Object"))
					{
						GameObject* newGameObject = new GameObject(name, Shape::Triangle);
						newGameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);
						newGameObject->GetComponent<RenderComponent>()->setTexture("../white_engine_core/Texture/container.jpg");

						if (hasSound)
							newGameObject->AddComponent<SoundManager>();

						if (hasPhysics)
						{
							newGameObject->AddComponent<PhysicComponent>();
							newGameObject->AddComponent<ColliderComponent>();
						}

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

