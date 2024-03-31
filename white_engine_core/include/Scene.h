#pragma once

#include <vector>
#include <string>

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
    GameObject* GetObject(std::string Name);
    void UpdateScene(float deltaTime);
    void RenderObjects(GLFWwindow* window);

    std::vector<GameObject*> getObjects();

     /**
     * \brief : Function that display the imgui windows for the editor DEBUG ONLY
     * \param
     *  int score : the score to display
    */
    void DrawDebug(int score);

private:
    std::vector<GameObject*> objects;
};
