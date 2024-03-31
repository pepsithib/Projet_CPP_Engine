#pragma once
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>

class EventSystem
{
public:
    using EventCallback = std::function<void()>;

    static EventSystem* getInstance();

    /**
    * \brief : Function to add an event
    * \param : 
    * eventName : Name tie to an event
    * callback : function call when the event his trigger
    */
    void AddEventListener(const std::string& eventName, const EventCallback& callback);

    /**
    * \brief : Function to add an event
    * \param :
    * eventName : Name tie to an event
    */
    void TriggerEvent(const std::string& eventName);

private:
    EventSystem() = default;
    ~EventSystem() = default;
    EventSystem(const EventSystem&) = delete;
    EventSystem& operator=(const EventSystem&) = delete;

    std::unordered_map<std::string, std::vector<EventCallback>> eventListeners;
    std::unordered_map<std::string, std::vector<EventCallback*>> callbackPointers; 

};


