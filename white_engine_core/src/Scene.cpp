#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddEntity(GameObject* object) {
    objects.push_back(object);
}

void Scene::RemoveEntity(GameObject* object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}


void Scene::Update(float deltaTime) {
    // Mettre à jour chaque GameObject dans la scène
    for (GameObject* gameObject : objects) {
        gameObject->Update(deltaTime);
    }
}

void Scene::Render() {
    for (GameObject* object : objects) {
        object->Render();
    }

