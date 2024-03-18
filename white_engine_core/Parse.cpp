#include "Parse.h"
#include "Scene.h"
#include "GameObject/GameObject.h"
#include <Component/TransformComponent.h>
#include <Component/SoundManager.h>
#include <Component/PhysicComponent.h>
#include <Component/RenderComponent.h>
#include <Component/ColliderComponent.h>
#include "Sound.h"
#include <iostream>

json JSONParser::serializeFlipper(Scene* flipper) {
    json serializedFlipper;
    for (GameObject* i : flipper->getObjects())
    {

        serializedFlipper["Scene"][i->GetFriendlyName()]["Transform"] = {
            {"PositionX", i->GetComponent<TransformComponent>()->GetWorldPosition().x},
            {"PositionY", i->GetComponent<TransformComponent>()->GetWorldPosition().y},
            {"Rotation", i->GetComponent<TransformComponent>()->GetRotation()},
            {"ScaleX", i->GetComponent<TransformComponent>()->GetScale().x},
            {"ScaleY", i->GetComponent<TransformComponent>()->GetScale().y}
        };

        if (i->GetComponent<SoundManager>() != nullptr)
        {
            std::vector<json> soundAttachToComponent = {};
            for (Sound* j : i->GetComponent<SoundManager>()->getSoundList())
            {
                soundAttachToComponent.push_back({ j->name, j->soundPath });
            }
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["list"] = soundAttachToComponent;
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["state"] = "enable";
        }
        else
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["state"] = "disable";
        }

        if (i->GetComponent<PhysicComponent>() != nullptr)
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Physics"] = {
                { "state", "enable" },
                {"VelocityX", i->GetComponent<PhysicComponent>()->getVelocity().x},
                {"VelocityY", i->GetComponent<PhysicComponent>()->getVelocity().y},
                {"AccelerationX", i->GetComponent<PhysicComponent>()->getAcceleration().x},
                {"AccelerationY", i->GetComponent<PhysicComponent>()->getAcceleration().y},
            };
        }
        else
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Physics"]["state"] = "disable";
        }

        if (i->GetComponent<ColliderComponent>() != nullptr)
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Collider"]["state"] = "enable" ;
        }
        else
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Collider"]["state"] =  "disable";
        }

        serializedFlipper["Scene"][i->GetFriendlyName()]["Render"] = {
            {"Texture", i->GetComponent<RenderComponent>()->getTexturePath()}
        };

        serializedFlipper["Scene"][i->GetFriendlyName()]["Shape"] = i->GetShape();

        gOnameList.push_back(i->GetFriendlyName());
    }

    return serializedFlipper;
}

void JSONParser::deserializeFlipper(const json& save, Scene& flipper) {
    
    for (int i = 0; i < gOnameList.size(); i++)
    {
        Shape shape = Shape::None;
        switch (save["Scene"][gOnameList[i]]["Shape"].template get<int>())
        {
            case 0:
                shape = Shape::None;
                break;
            case 1:
                shape = Shape::Circle;
                break;
            case 2 :
                shape = Shape::Rectangle;
                break;
            case 3:
                shape = Shape::Triangle;
                break;
        }

        GameObject* go = new GameObject(gOnameList[i], shape);
        
        go->GetComponent<TransformComponent>()->SetWorldPosition({ save["Scene"][gOnameList[i]]["Transform"]["PositionX"], save["Scene"][gOnameList[i]]["Transform"]["PositionY"] });
        go->GetComponent<TransformComponent>()->SetRotation(save["Scene"][gOnameList[i]]["Transform"]["Rotation"]);
        go->GetComponent<TransformComponent>()->SetScale({ save["Scene"][gOnameList[i]]["Transform"]["ScaleX"], save["Scene"][gOnameList[i]]["Transform"]["ScaleY"] });

        go->GetComponent<RenderComponent>()->setTexture(save["Scene"][gOnameList[i]]["Render"]["Texture"]);

        if (save["Scene"][gOnameList[i]]["Sounds"]["state"] == "enable")
        {
            go->AddComponent<SoundManager>();
            for (auto i : save["Scene"][gOnameList[i]]["Sounds"]["list"])
            {
                go->GetComponent<SoundManager>()->addSound(i[1], i[0]);
            }
        }

        if (save["Scene"][gOnameList[i]]["Physics"]["state"] == "enable")
        {
            go->AddComponent<PhysicComponent>();
            go->GetComponent<PhysicComponent>()->setVelocity({ save["Scene"][gOnameList[i]]["Physics"]["VelocityX"], save["Scene"][gOnameList[i]]["Physics"]["VelocityY"] });
            go->GetComponent<PhysicComponent>()->setAcceleration({ save["Scene"][gOnameList[i]]["Physics"]["AccelerationX"], save["Scene"][gOnameList[i]]["Physics"]["AccelerationX"] });
        }

        if (save["Scene"][gOnameList[i]]["Collider"]["state"] == "enable")
        {
            go->AddComponent<ColliderComponent>();
        }

        flipper.AddEntity(go);
    }
}