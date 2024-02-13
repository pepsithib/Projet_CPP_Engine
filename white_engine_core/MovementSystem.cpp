#include "MovementSystem.h"

MovementSystem::MovementSystem() {}

MovementSystem::~MovementSystem() {}

void MovementSystem::update(std::vector<Position>& positions, std::vector<Velocity>& velocities, float dt) {
    for (size_t i = 0; i < positions.size(); ++i) {
        positions[i].x += velocities[i].dx * dt;
        positions[i].y += velocities[i].dy * dt;
    }
}
