#pragma once

#include <vector>


#define DEBUG_INFO_SIZE 30

class GameObject;
struct GLFWwindow;

class Scene {
public:
    Scene();
    ~Scene();

    void AddEntity(GameObject* object);
    void RemoveEntity(GameObject* object);
    std::vector<GameObject*> GetObjects() { return objects; };
    void UpdateScene(float deltaTime);
    void RenderObjects(GLFWwindow* window);

    std::vector<GameObject*> getObjects();

     /**
     * \brief : Function that display the imgui windows for the editor DEBUG ONLY
     * \param
     *  object : list of Game object to edit : position, rotation, scale, texture can be edit, a gameObject can be delete to
    */
    void DrawDebug();

private:
    std::vector<GameObject*> objects;
};
