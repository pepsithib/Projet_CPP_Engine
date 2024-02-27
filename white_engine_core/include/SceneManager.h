#pragma once

#include <vector>

class Scene;
class GLFWwindow;

class SceneManager {
public:
    SceneManager();
    ~SceneManager();

    void addScene(Scene* scene);
    void changeScene(size_t index);
    void update(float dt);
    void render(GLFWwindow* window);

private:
    std::vector<Scene*> scenes;
    size_t currentSceneIndex;
};
