#pragma once

#include <vector>

struct Position {
    float x, y;
};

struct Velocity {
    float dx, dy;
};

class MovementSystem;
class RenderingSystem;

class Scene {
public:
    Scene();
    ~Scene();

    void addEntity(const Position& initialPosition, const Velocity& initialVelocity);
    void update(float dt);
    void render();

private:
    std::vector<Position> positions;
    std::vector<Velocity> velocities;
    MovementSystem* movementSystem;
    RenderingSystem* renderingSystem;
};
