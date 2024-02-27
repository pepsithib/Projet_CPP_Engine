#include "SceneManager.h"
#include "Scene.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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
        scenes[currentSceneIndex]->Update(dt);
}

void SceneManager::render(GLFWwindow* window) {
    if (currentSceneIndex < scenes.size())
        scenes[currentSceneIndex]->Render(window);
}
