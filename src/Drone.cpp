#include "Drone.h"
#include "MissionQueue.h"
#include <iostream>


// El constructor inicializa los miembros y lanza el hilo
// El hilo comienza a ejecutar Drone::run() inmediatamente
Drone::Drone(int droneId, MissionQueue& queue, std::atomic<bool>& signal) 
    : id(droneId), state(DroneState::IDLE), mission_queue(queue), stop_signal(signal) {
    droneThread = std::thread(&Drone::run, this);
}

// El destructor se asegura de que el hilo se una (termine) antes de que el objeto Drone sea destruido
Drone::~Drone() {
    // joinable() comprueba si el hilo esta activo
    if (droneThread.joinable()) {
        droneThread.join(); // El hilo principal espera aqui a que el droneThread termine
    }
}

// El "ciclo de vida" del dron
void Drone::run() {
    std::cout << "Drone " << id << " operational." << std::endl;

    while (!stop_signal) {
        std::unique_ptr<Mission> mission_to_execute = mission_queue.getNextMission();

        if (mission_to_execute) {
            state = DroneState::WORKING;
            std::cout << "Drone " << id << " picked up mission " << mission_to_execute->getId() << "." << std::endl;
            mission_to_execute->execute();
            state = DroneState::IDLE;
        } else {
            // Si no hay misiones, el drone espera un poco antes de volver a comprobar.
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    std::cout << "Drone " << id << " shutting down." << std::endl;
    
}