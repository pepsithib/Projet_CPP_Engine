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

json JSONParser::serializeFlipper(Scene* sceneToSave) {

    json serializedFlipper;
    int order = 0;

    /* Get all the gameObject in the scene */
    for (GameObject* i : sceneToSave->getObjects())
    {
        serializedFlipper["Scene"][i->GetFriendlyName()]["Order"] = order;
        order++;
        
        /* Save Tags */
        if (!i->GetTags().empty())
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Tags"] =
            {
                {"state", "enable"},
                {"TagsList", i->GetTags()},
            };
            
        }
        else
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Tags"]["state"] = "disable";
        }

        /* Save the Transform Component */
        serializedFlipper["Scene"][i->GetFriendlyName()]["Transform"] = {
            {"PositionX", i->GetComponent<TransformComponent>()->GetWorldPosition().x},
            {"PositionY", i->GetComponent<TransformComponent>()->GetWorldPosition().y},
            {"Rotation", i->GetComponent<TransformComponent>()->GetRotation()},
            {"ScaleX", i->GetComponent<TransformComponent>()->GetScale().x},
            {"ScaleY", i->GetComponent<TransformComponent>()->GetScale().y},
            {"PivotX", i->GetComponent<TransformComponent>()->GetPivot().x},
            {"PivotY", i->GetComponent<TransformComponent>()->GetPivot().y},
        };

        /* Save the Sound Component */
        if (i->GetComponent<SoundManager>() != nullptr)
        {
            std::vector<json> soundAttachToComponent = {};

            /* Get all the sound attach to the gameObject */
            for (Sound* j : i->GetComponent<SoundManager>()->getSoundList())
            {
                soundAttachToComponent.push_back({ j->name, j->soundPath });
            }
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["list"] = soundAttachToComponent;

            /* if the gameObject as this component, set the state as enable */
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["state"] = "enable";
        }
        else
        {
            /* if not set the state at disable */
            serializedFlipper["Scene"][i->GetFriendlyName()]["Sounds"]["state"] = "disable";
        }

        /* Save the Physics Component */
        if (i->GetComponent<PhysicComponent>() != nullptr)
        {
            serializedFlipper["Scene"][i->GetFriendlyName()]["Physics"] = {
                /* if the gameObject as this component, set the state as enable */
                { "state", "enable" },

                {"VelocityX", i->GetComponent<PhysicComponent>()->getVelocity().x},
                {"VelocityY", i->GetComponent<PhysicComponent>()->getVelocity().y},
                {"AccelerationX", i->GetComponent<PhysicComponent>()->getAcceleration().x},
                {"AccelerationY", i->GetComponent<PhysicComponent>()->getAcceleration().y},
                {"IsStatic", i->GetComponent<PhysicComponent>()->getStatic()},
            };
        }
        else
        {
            /* if not set the state at disable */
            serializedFlipper["Scene"][i->GetFriendlyName()]["Physics"]["state"] = "disable";
        }

        if (i->GetComponent<ColliderComponent>() != nullptr)
        {
            /* if the gameObject as this component, set the state as enable */
            serializedFlipper["Scene"][i->GetFriendlyName()]["Collider"] = {
                {"state" , "enable"},
                {"IsStatic", i->GetComponent<ColliderComponent>()->isStatic()},
            };
        }
        else
        {
            /* if not set the state at disable */
            serializedFlipper["Scene"][i->GetFriendlyName()]["Collider"]["state"] =  "disable";
        }

        /* Save the Texture path */
        serializedFlipper["Scene"][i->GetFriendlyName()]["Render"] = {
            {"Texture", i->GetComponent<RenderComponent>()->getTexturePath()}
        };

        /* Save the gameObject Shape (circle, rectangle, triangle) */
        serializedFlipper["Scene"][i->GetFriendlyName()]["Shape"] = i->GetShape();
    }

    /* return the json with the scene state */
    return serializedFlipper;
}

void JSONParser::deserializeFlipper(json& save, Scene& sceneToReload) {
    /* Get all gameObject name and order */
    for (int inc = 0; inc < 13; inc++)
    {
        for (auto j : save["Scene"].items())
        {
            if (save["Scene"][j.key()]["Order"].template get<int>() == inc) {
                gOnameList.push_back(j.key());
            }
        }
    }
    
    /* For all gameObject */
    for (int i = 0; i < gOnameList.size(); i++)
    {
        /* Get the right shape with the number store */
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

        /* Create new gameObject */
        GameObject* go = new GameObject(gOnameList[i], shape);
        
        /* Set Transform */
        go->GetComponent<TransformComponent>()->SetWorldPosition({ save["Scene"][gOnameList[i]]["Transform"]["PositionX"], save["Scene"][gOnameList[i]]["Transform"]["PositionY"] });
        go->GetComponent<TransformComponent>()->SetRotation(save["Scene"][gOnameList[i]]["Transform"]["Rotation"]);
        go->GetComponent<TransformComponent>()->SetScale({ save["Scene"][gOnameList[i]]["Transform"]["ScaleX"], save["Scene"][gOnameList[i]]["Transform"]["ScaleY"] });
        go->GetComponent<TransformComponent>()->SetPivot({ save["Scene"][gOnameList[i]]["Transform"]["PivotX"], save["Scene"][gOnameList[i]]["Transform"]["PivotY"] });

        /* Set Texture */
        go->GetComponent<RenderComponent>()->setTexture(save["Scene"][gOnameList[i]]["Render"]["Texture"]);

        /* If this gameObject as the SoundManager Component, add it */
        if (save["Scene"][gOnameList[i]]["Sounds"]["state"] == "enable")
        {
            /* Add each sound */
            go->AddComponent<SoundManager>();
            for (auto i : save["Scene"][gOnameList[i]]["Sounds"]["list"])
            {
                go->GetComponent<SoundManager>()->addSound(i[1], i[0]);
            }
        }

        /* If this gameObject as the SoundManager Component, add it */
        if (save["Scene"][gOnameList[i]]["Physics"]["state"] == "enable")
        {
            go->AddComponent<PhysicComponent>();
            go->GetComponent<PhysicComponent>()->setVelocity({ save["Scene"][gOnameList[i]]["Physics"]["VelocityX"], save["Scene"][gOnameList[i]]["Physics"]["VelocityY"] });
            go->GetComponent<PhysicComponent>()->setAcceleration({ save["Scene"][gOnameList[i]]["Physics"]["AccelerationX"], save["Scene"][gOnameList[i]]["Physics"]["AccelerationX"] });
            
            if (save["Scene"][gOnameList[i]]["Physics"]["IsStatic"] == true)
                go->GetComponent<PhysicComponent>()->setStatic();
        }

        /* If this gameObject as the Collider Component, add it */
        if (save["Scene"][gOnameList[i]]["Collider"]["state"] == "enable")
        {
            go->AddComponent<ColliderComponent>();
            if (save["Scene"][gOnameList[i]]["Collider"]["IsStatic"] == true)
                go->GetComponent<ColliderComponent>()->setStatic();
        }

        /* If the gameObject as tags, set them */
        if (save["Scene"][gOnameList[i]]["Tags"]["state"] == "enable")
        {
            for (auto y : save["Scene"][gOnameList[i]]["Tags"]["TagsList"])
            {
                go->AddTag(y);
            }

        }

        /* Add the Entity to the new scene */
        sceneToReload.AddEntity(go);
    }
    
    gOnameList.clear();
}