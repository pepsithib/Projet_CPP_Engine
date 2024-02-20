#pragma once

#include <vector>
#include <RenderComponent.h>
#include <GameObject.h>
#include <Scene.h>

class Scene {
public:
    Scene();
    ~Scene();

    void addEntity(GameObject* object);
    void removeEntity(GameObject* object);
    //void update();
    //void render();

private:
    std::vector<GameObject*> objects;

};
