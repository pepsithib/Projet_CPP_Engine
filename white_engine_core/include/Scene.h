#pragma once

#include <vector>
#include <Component/RenderComponent.h>
#include <GameObject/GameObject.h>
#include <Component/TransformComponent.h>

class Scene {
public:
    Scene();
    ~Scene();

    void AddEntity(GameObject* object);
    void RemoveEntity(GameObject* object);
    void Update(float deltaTime);
    void Render();

private:
    std::vector<GameObject*> objects;

};
