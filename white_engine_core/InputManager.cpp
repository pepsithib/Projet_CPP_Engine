#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window) : window(window) {}

InputManager::~InputManager() {}

bool InputManager::IsLeftArrowPressed() {
    return glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
}

bool InputManager::IsRightArrowPressed() {
    return glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
}

bool InputManager::IsSpaceBarPressed() {
    return glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
}