#include "EventSystem.h"

/* Add observer to an event */
void EventSystem::AddEventListener(const std::string& eventName, const EventCallback& callback) {
    eventListeners[eventName].push_back(callback);
    /* copie the callback and stock his address */
    callbackPointers[eventName].push_back(new EventCallback(callback));
}


/* Triggering */
void EventSystem::TriggerEvent(const std::string& eventName) {
    auto it = eventListeners.find(eventName);
    if (it != eventListeners.end()) {
        for (const auto& listener : it->second) {
            listener();
        }
    }
}

EventSystem* EventSystem::getInstance() {
    static EventSystem instance; 
    return &instance;
}