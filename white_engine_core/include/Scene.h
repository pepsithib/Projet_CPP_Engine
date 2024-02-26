#pragma once

#include <vector>
#include <RenderComponent.h>
#include <GameObject.h>
#include <TransformComponent.h>

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
