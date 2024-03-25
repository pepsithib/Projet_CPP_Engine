#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

struct InputState {
    bool leftArrowPressed;
    bool rightArrowPressed;
    bool spaceBarPressed;

    InputState() : leftArrowPressed(false), rightArrowPressed(false), spaceBarPressed(false) {}
};

class InputManager {
public:
    static InputManager& getInstance(GLFWwindow* window);

    void updateInputState();

    const InputState& getInputState() const { return inputState; }

private:
    InputManager(GLFWwindow* window);
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    GLFWwindow* window;
    InputState inputState;
};
