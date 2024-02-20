#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {}

void Scene::addEntity(GameObject* object) {
    objects.push_back(object);
}

void Scene::removeEntity(GameObject* object) {
    auto it = std::find(objects.begin(), objects.end(), object);
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void Scene::update() {
}

void Scene::render() {
    for (GameObject* object : objects) {
        object->Render();
    }

