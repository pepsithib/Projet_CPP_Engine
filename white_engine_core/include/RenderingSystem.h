#pragma once

#include <vector>


struct Position {
    float x, y;
};

class RenderingSystem {
public:
    RenderingSystem();
    ~RenderingSystem();

    void render(const std::vector<Position>& positions);
};
