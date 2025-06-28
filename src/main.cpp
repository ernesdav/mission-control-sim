#include <iostream>
#include <memory>
#include <vector>

#include "MissionQueue.h"
#include "SurveillanceMission.h"
#include "DeliveryMission.h"
#include "Drone.h"

int main() {
    std::cout << "--- Mission Control Simulator Initializing Fleet ---" << std::endl;

    // Creamos nuestra flota de drones.
    // Al crearse, cada dron lanzará su propio hilo.
    std::vector<std::unique_ptr<Drone>> fleet;
    for (int i = 1; i <= 3; ++i) {
        fleet.push_back(std::make_unique<Drone>(i));
    }

    std::cout << "\nFleet of " << fleet.size() << " drones deployed. Main thread is standing by." << std::endl;
    std::cout << "The program will terminate when all drones complete their lifecycle (approx. 10s)." << std::endl;

    // El programa principal esperará aquí.
    // Cuando 'main' termine, los unique_ptr en el vector 'fleet' se destruirán.
    // Al destruirse, se llamará al destructor de cada Drone.
    // El destructor de cada Drone llamará a 'droneThread.join()',
    // asegurando que el programa espere a que todos los hilos terminen.

    return 0;
}