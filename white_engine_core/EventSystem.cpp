#include "EventSystem.h"

// Ajouter un observateur à un événement spécifique
void EventSystem::AddEventListener(const std::string& eventName, const EventCallback& callback) {
    eventListeners[eventName].push_back(callback);
    // Créer une copie du callback et stocker son adresse
    callbackPointers[eventName].push_back(new EventCallback(callback));
}

// Supprimer un observateur d'un événement spécifique
//void EventSystem::RemoveEventListener(const std::string& eventName, const EventCallback& callback) {
//    auto it = eventListeners.find(eventName);
//    if (it != eventListeners.end()) {
//        auto& listeners = it->second;
//        auto& pointers = callbackPointers[eventName];
//        for (auto listenerIt = listeners.begin(); listenerIt != listeners.end(); ++listenerIt) {
//            for (auto pointer : pointers) {
//                if (*listenerIt == *pointer) { // Comparaison des pointeurs
//                    if (listenerIt != listeners.end()) {
//                        listenerIt = listeners.erase(listenerIt); // Suppression du callback du vecteur
//                    }
//                    // Suppression du pointeur
//                    pointers.erase(std::remove(pointers.begin(), pointers.end(), pointer), pointers.end());
//                    delete pointer; // Suppression de la mémoire allouée
//                    break; 
//                }
//            }
//        }
//    }
//}


// Déclencherment
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