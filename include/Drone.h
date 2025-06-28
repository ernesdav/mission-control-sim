#ifndef DRONE_H
#define DRONE_H

#include <thread>
#include <atomic>

// Forward declarations para evitar includes circulares
class MissionQueue;
// posibles estados del dron
enum class DroneState { IDLE, WORKING};

class Drone {
private:
    int id;
    std::atomic<DroneState> state;  // std::atomic para seguridad en concurrencia
    std::thread droneThread;
    MissionQueue& mission_queue;  // Referencia a la cola compartida
    std::atomic<bool>& stop_signal;  // Referencia a la señal de parada compartida

    void run();  // esta funcion la ejecutara el hilo en bucle

public:
    Drone(int droneId, MissionQueue& queue, std::atomic<bool>& signal);  // el constructor inicia el hilo
    ~Drone();  // el destructor se asegura que el hilo termine limpiamente

    // Para evitar que la clase se puede copiar, lo que complicaria la gestion del hilo
    Drone(const Drone&) = delete;
    Drone& operator=(const Drone&) = delete;
};

#endif