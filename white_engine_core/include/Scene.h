#pragma once

#include <vector>

class GameObject;
class GLFWwindow;

class Scene {
public:
    Scene();
    ~Scene();

    void AddEntity(GameObject* object);
    void RemoveEntity(GameObject* object);
    void Update(float deltaTime);
    void Render(GLFWwindow* window);

private:
    std::vector<GameObject*> objects;

};
