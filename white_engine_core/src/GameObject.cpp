#include "GameObject.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include <iostream>

// Constructor for GameObject class
GameObject::GameObject(std::string friendlyName, float* matrix, Shape shape) : matrix(matrix), shape(shape)
{
    // Add TransformComponent and RenderComponent to the GameObject
    AddComponent<TransformComponent>();
    AddComponent<RenderComponent>();
}

// Destructor for GameObject class
GameObject::~GameObject()
{
    // Destroy and deallocate memory for each component
    for (IComponent* component : Components) {
        component->Destroy();
        delete component;
    }
    delete matrix; // Deallocate memory for the matrix
}

// Update function for GameObject
void GameObject::Update(float deltaTime)
{
    // Call the Update function for each component
    for (IComponent* component : Components) {
        component->Update(deltaTime);
    }
}

// Render function for GameObject
void GameObject::Render() {
    for (IComponent* component : Components) {
        if (component->GetComponentName() == "Renderer") { // Vérifiez si le composant est un RenderComponent
            RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
            if (renderComponent != nullptr) {
                renderComponent->Draw(); // Appelez la fonction Draw() de RenderComponent
            }
        }
    }
}

// Draw function for GameObject
void GameObject::Draw()
{
    // Obtenez le composant de rendu du GameObject
    RenderComponent* renderComponent = GetComponent<RenderComponent>();

    if (renderComponent) {
        // Si un composant de rendu est présent, utilisez-le pour rendre l'objet
        renderComponent->Draw();
    }
    else {
        // Si aucun composant de rendu n'est présent, vous pouvez toujours dessiner quelque chose de basique
        // Cela dépendra de votre logique spécifique
        std::cout << "No render component found for GameObject: " << FriendlyName << std::endl;
    }
}

// Get the friendly name of the GameObject
const std::string& GameObject::GetFriendlyName() const
{
    return FriendlyName;
}

// Change the shape of the GameObject
void GameObject::ChangeShape(Shape shape)
{
    this->shape = shape;
}

// Get the shape of the GameObject
Shape GameObject::GetShape()
{
    return shape;
}

// Update the matrix of the GameObject with new vertex data
void GameObject::UpdateMatrix(float* vertex, int size)
{
    delete matrix; // Deallocate the previous matrix
    matrix = new float[size](); // Allocate memory for the new matrix
    memcpy(matrix, vertex, sizeof(float) * size); // Copy vertex data into the matrix
}

// Get the matrix of the GameObject
float* GameObject::GetMatrix()
{
    return matrix;
}
