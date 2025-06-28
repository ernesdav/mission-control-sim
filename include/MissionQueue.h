#ifndef MISSION_QUEUE_H
#define MISSION_QUEUE_H

#include "Mission.h"
#include <queue>    // Para std::priority_queue
#include <vector>
#include <memory>   // Para std::unique_ptr y std::move
#include <mutex>

// 1. Comparador Personalizado para la Cola de Prioridad
// La mision con menor valor de prioridad es la que mayor prioridad tendra en la cola
struct MissionComparator {
    bool operator()(const std::unique_ptr<Mission>& a, const std::unique_ptr<Mission>& b) const {
        return a->getPriority() > b->getPriority();
    }
};

// 2. La clase que gestiona la cola de misiones
class MissionQueue {
private:
    // - Almacna punteros inteligente a Mission
    // - Usa un std::vector internamente para guardar los elementos
    // - Usa MissionComparator para ordenarlos
    std::priority_queue<
        std::unique_ptr<Mission>,
        std::vector<std::unique_ptr<Mission>>,
        MissionComparator
    > queue;

    std::mutex queue_mutex;

public:
    // Añade una misión a la cola
    // Toma posesión del puntero usando std::move
    void addMission(std::unique_ptr<Mission> mission) {
        // Bloquea el mutex. Se desbloqueara automaticamente cuando 'lock' se destruya al final de la funcion
        std::lock_guard<std::mutex> lock(queue_mutex);
        queue.push(std::move(mission));
    }

    // Obtiene la siguiente mision de mayor prioridad
    // Transfiere la posesion del puntero fuera de la cola
    std::unique_ptr<Mission> getNextMission() {
        if(queue.empty()) {
            return nullptr;
        }
        // std::move es necesario para transferir la propiedad del unique_ptr fuera de la cola
        std::unique_ptr<Mission> mission = std::move(const_cast<std::unique_ptr<Mission>&>(queue.top()));
        queue.pop();
        return mission;
    }

    bool isEmpty() const {
        return queue.empty();
    }
};

#endif