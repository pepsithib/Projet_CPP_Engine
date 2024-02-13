#include "Scene.h"
#include "MovementSystem.h"
#include "RenderingSystem.h"

Scene::Scene() : movementSystem(new MovementSystem()), renderingSystem(new RenderingSystem()) {}

Scene::~Scene() {
    delete movementSystem;
    delete renderingSystem;
}

void Scene::addEntity(const Position& initialPosition, const Velocity& initialVelocity) {
    positions.push_back(initialPosition);
    velocities.push_back(initialVelocity);
}

void Scene::update(float dt) {
    movementSystem->update(positions, velocities, dt);
}

void Scene::render() {
    renderingSystem->render(positions);
}
