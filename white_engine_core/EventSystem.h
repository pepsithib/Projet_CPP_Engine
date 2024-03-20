#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

class EventSystem
{
public:
    using EventCallback = std::function<void()>;

    // Ajouter un observateur � un �v�nement sp�cifique
    void AddEventListener(const std::string& eventName, const EventCallback& callback);

    // Supprimer un observateur d'un �v�nement sp�cifique
    void RemoveEventListener(const std::string& eventName, const EventCallback& callback);

    // D�clenchement event
    void TriggerEvent(const std::string& eventName);

private:
    std::unordered_map<std::string, std::vector<EventCallback>> eventListeners;
    std::unordered_map<std::string, std::vector<EventCallback*>> callbackPointers;
};


