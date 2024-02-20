#pragma once
#include "IComponent.h"
#include "Texture.h"

class TransformComponent;
class IDrawable;

class RenderComponent :
    public IComponent
{

public:

    RenderComponent(GameObject& GameObject);
    ~RenderComponent();

    void setTexture(std::string path);

    virtual void Start() override;

    virtual void Update(float deltaTime) override;

    virtual void Destroy() override;

    void Draw();

    static const std::string GetComponentName_Static();
    virtual const std::string GetComponentName() const override;

private :
    Texture* texture;
};

