#ifndef DRONE_H
#define DRONE_H

#include <thread>
#include <atomic>

// posibles estados del dron
enum class DroneState { IDLE, MISSION_IN_PROGRESS, RETURNING, MAINTENANCE};

class Drone {
private:
    int id;
    std::atomic<DroneState> state;  // std::atomic para seguridad en concurrencia
    std::thread droneThread;

    void run();  // esta funcion la ejecutara el hilo en bucle

public:
    Drone(int droneId);  // el constructor inicia el hilo
    ~Drone();  // el destructor se asegura que el hilo termine limpiamente

    // Para evitar que la clase se puede copiar, lo que complicaria la gestion del hilo
    Drone(const Drone&) = delete;
    Drone& operator=(const Drone&) = delete;
};

#endif