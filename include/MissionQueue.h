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
    bool operator()(const std::shared_ptr<Mission>& a, const std::shared_ptr<Mission>& b) const {
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
        std::shared_ptr<Mission>,
        std::vector<std::shared_ptr<Mission>>,
        MissionComparator
    > queue;

    mutable std::mutex queue_mutex;

public:
    // Añade una misión a la cola
    // Toma posesión del puntero usando std::move
    void addMission(std::shared_ptr<Mission> mission) {
        // Bloquea el mutex. Se desbloqueara automaticamente cuando 'lock' se destruya al final de la funcion
        std::lock_guard<std::mutex> lock(queue_mutex);
        queue.push(mission);
    }

    // Obtiene la siguiente mision de mayor prioridad
    // Transfiere la posesion del puntero fuera de la cola
    std::shared_ptr<Mission> getNextMission() {
        std::lock_guard<std::mutex> lock(queue_mutex);
        if(queue.empty()) {
            return nullptr;
        }
        // Copiamos el shared_ptr de forma segura. El contador de referencias aumenta
        std::shared_ptr<Mission> mission = queue.top();
        queue.pop();  // Eliminamos el puntero de la cola. El contador de referencias baja.
        return mission;
    }

    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(queue_mutex);
        return queue.empty();
    }
};

#endif