#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

class EventSystem
{
public:
    using EventCallback = std::function<void()>;

    static EventSystem* getInstance(); // Méthode pour obtenir l'instance unique de EventSystem

    void AddEventListener(const std::string& eventName, const EventCallback& callback);
    void RemoveEventListener(const std::string& eventName, const EventCallback& callback);
    void TriggerEvent(const std::string& eventName);

private:
    EventSystem() = default;
    ~EventSystem() = default;
    EventSystem(const EventSystem&) = delete;
    EventSystem& operator=(const EventSystem&) = delete;

    std::unordered_map<std::string, std::vector<EventCallback>> eventListeners;
    std::unordered_map<std::string, std::vector<EventCallback*>> callbackPointers; 

};


