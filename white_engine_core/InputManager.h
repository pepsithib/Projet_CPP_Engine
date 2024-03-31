#pragma once
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>

/*
* Contain nearly all of GLFW key
*/
enum InputKey
{
    SPACE = 32,
    APOSTROPHE = 39,
    COMMA = 44,
    MINUS,
    PERIOD,
    SLASH,
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SEMICOLON = 59,
    EQUAL = 61,
    A = 65,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,
    LEFT_BRACKET,
    BACKSLASH,
    RIGHT_BRACKET,
    GRAVE_ACCENT = 96,
    WORLD_1 = 161,
    WORLD_2 = 162,
    ESCAPE = 256,
    ENTER,
    TAB,
    BACKSPACE,
    INSERT,
    DELETE,
    RIGHT,
    LEFT,
    DOWN,
    UP,
    PAGE_UP,
    PAGE_DOWN,
    HOME,
    END,
    CAPS_LOCK = 280,
    SCROLL_LOCK,
    NUM_LOCK,
    PRINT_SCREEN,
    PAUSE,
    F1 = 290,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    KP0 = 320,
    KP1,
    KP2,
    KP3,
    KP4,
    KP5,
    KP6,
    KP7,
    KP8,
    KP9,
    DECIMAL,
    DIVIDE,
    MULTIPLY,
    SUBTRACT,
    ADD,
    KPENTER,
    KPEQUAL,
    LEFT_SHIFT = 340,
    LEFT_CONTROL,
    LEFT_ALT,
    LEFT_SUPER,
    RIGHT_SHIFT,
    RIGHT_CONTROL,
    RIGHT_ALT,
    RIGHT_SUPER,
    MENU,
    LAST = MENU,
};





class InputManager {
public:
    static InputManager* getInstance(GLFWwindow* window);

    void updateInputState();

    const std::map<InputKey,bool> getInputState() const { return mapState; }

    void AddInputToWatch(InputKey key);

    bool CheckInput(InputKey key);

private:
    InputManager(GLFWwindow* window);
    ~InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager& operator=(const InputManager&) = delete;

    GLFWwindow* window;
    std::map<InputKey, bool> mapState;
};
