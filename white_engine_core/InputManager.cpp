#include "InputManager.h"

InputManager::InputManager(GLFWwindow* window) : window(window) {
    // Initialisation de votre classe InputManager si nécessaire
}

InputManager& InputManager::getInstance(GLFWwindow* window) {
    static InputManager instance(window); // Instance statique unique
    return instance;
}

void InputManager::updateInputState() {
    inputState.leftArrowPressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    inputState.rightArrowPressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    inputState.spaceBarPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
}