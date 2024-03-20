#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

class InputManager
{
public:
    InputManager(GLFWwindow* window); 
    ~InputManager();

    bool IsLeftArrowPressed(); // Fl�che de gauche
    bool IsRightArrowPressed(); // Fl�che de droite
    bool IsSpaceBarPressed(); // Barre espace

private:
    GLFWwindow* window;
};

