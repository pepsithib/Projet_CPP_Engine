#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() : currentSceneIndex(0) {}

SceneManager::~SceneManager() {
    // Nettoyage des scènes
    for (auto scene : scenes) {
        delete scene;
    }
}

void SceneManager::addScene(Scene* scene) {
    scenes.push_back(scene);
}

void SceneManager::changeScene(size_t index) {
    if (index < scenes.size())
        currentSceneIndex = index;
}

void SceneManager::update(float dt) {
    if (currentSceneIndex < scenes.size())
        scenes[currentSceneIndex]->update(dt);
}

void SceneManager::render() {
    if (currentSceneIndex < scenes.size())
        scenes[currentSceneIndex]->render();
}
