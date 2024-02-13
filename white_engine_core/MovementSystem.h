#pragma once

#include <vector>

struct Position;
struct Velocity;

class MovementSystem {
public:
    MovementSystem();
    ~MovementSystem();

    void update(std::vector<Position>& positions, std::vector<Velocity>& velocities, float dt);
};
