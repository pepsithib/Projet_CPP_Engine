#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window) : window(window) {

}


InputManager* InputManager::getInstance(GLFWwindow* window) {
    static InputManager instance(window); /* Unique staique instance */
    return &instance;
}

void InputManager::updateInputState() {

    for (auto& [Key, state] : mapState) {
        state = glfwGetKey(window, Key) == GLFW_PRESS;
    }
}

void InputManager::AddInputToWatch(InputKey key)
{
    mapState.insert({key,false});
}

bool InputManager::CheckInput(InputKey key)
{
    return mapState.at(key);
}


