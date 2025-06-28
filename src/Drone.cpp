#include "Drone.h"
#include <iostream>
#include <chrono>

// El constructor inicializa los miembros y lanza el hilo
// El hilo comienza a ejecutar Drone::run() inmediatamente
Drone::Drone(int droneId) : id(droneId), state(DroneState::IDLE) {
    // Lanzamos el hilo, le decimos que ejecute el metodo 'run' de ESTE objeto
    droneThread = std::thread(&Drone::run, this);
    std::cout << "Drone " << id << " activated. Thread launched." << std::endl;
}

// El destructor se asegura de que el hilo se una (termine) antes de que el objeto Drone sea destruido
Drone::~Drone() {
    // joinable() comprueba si el hilo esta activo
    if (droneThread.joinable()) {
        droneThread.join(); // El hilo principal espera aqui a que el droneThread termine
    }
    std::cout << "Drone " << id << " deactivated." << std::endl;
}

// El "ciclo de vida" del dron
void Drone::run() {
    std::cout << "Drone " << id << " operational. Current state: IDLE." << std::endl;

    // Simular tiempo activo del dron y despues de apaga (para que el programa termine)
    std::this_thread::sleep_for(std::chrono::seconds(10));
    
}