#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class InputManager
{
public:
    InputManager(GLFWwindow* window); 
    ~InputManager();

    bool IsLeftArrowPressed(); // Flèche de gauche
    bool IsRightArrowPressed(); // Flèche de droite
    bool IsSpaceBarPressed(); // Barre espace

private:
    GLFWwindow* window;
};

