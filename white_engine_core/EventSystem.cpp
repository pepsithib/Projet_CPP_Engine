#include "EventSystem.h"

// Ajouter un observateur � un �v�nement sp�cifique
void EventSystem::AddEventListener(const std::string& eventName, const EventCallback& callback) {
    eventListeners[eventName].push_back(callback);
    // Cr�er une copie du callback et stocker son adresse
    callbackPointers[eventName].push_back(new EventCallback(callback));
}

//// Supprimer un observateur d'un �v�nement sp�cifique
//void EventSystem::RemoveEventListener(const std::string& eventName, const EventCallback& callback) {
//    auto it = eventListeners.find(eventName);
//    if (it != eventListeners.end()) {
//        auto& listeners = it->second;
//        for (auto listenerIt = listeners.begin(); listenerIt != listeners.end(); ++listenerIt) {
//            if (*listenerIt == callbackPointers[eventName]) { // Comparer les pointeurs de callback
//                listeners.erase(listenerIt);
//                break; // Sortir de la boucle une fois que l'�l�ment a �t� supprim�
//            }
//        }
//    }
//}

// D�clencherment
void EventSystem::TriggerEvent(const std::string& eventName) {
    auto it = eventListeners.find(eventName);
    if (it != eventListeners.end()) {
        for (const auto& listener : it->second) {
            listener();
        }
    }
}