#pragma once

#include <vector>

class Scene;
struct GLFWwindow;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void addScene(Scene* scene);
    void changeScene(size_t index);
    void update(float dt);
    void render(GLFWwindow* window);
    void setScene(int index, Scene* newScene);

private:
    std::vector<Scene*> scenes;
    size_t currentSceneIndex;
};
