#include "Scene.h"


Scene::Scene() {}

Scene::~Scene() {
    delete movementSystem;
    delete renderingSystem;
}

void Scene::addEntity(const Position& initialPosition, const Velocity& initialVelocity) {
    positions.push_back(initialPosition);
    velocities.push_back(initialVelocity);
}

void Scene::update(float dt) {

}

void Scene::render() {
 
}
