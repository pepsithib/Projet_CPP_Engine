#pragma once
#include "IComponent.h"

class TransformComponent;
class IDrawable;

class RenderComponent :
    public IComponent
{

public:

    RenderComponent(GameObject& GameObject);
    ~RenderComponent();

    virtual void Start() override;

    virtual void Update(float deltaTime) override;

    virtual void Destroy();

    void Draw(/* put the windows in here*/);
};

