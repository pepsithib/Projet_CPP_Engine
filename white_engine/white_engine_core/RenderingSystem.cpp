#include "RenderingSystem.h"
#include <GLFW/glfw3.h>

RenderingSystem::RenderingSystem() {}

RenderingSystem::~RenderingSystem() {}

void RenderingSystem::render(const std::vector<Position>& positions) {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (const auto& pos : positions) {
        glVertex2f(pos.x, pos.y);
    }
    glEnd();
}
