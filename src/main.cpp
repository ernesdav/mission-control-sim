#include <iostream>
#include <memory>
#include <vector>

#include "MissionQueue.h"
#include "SurveillanceMission.h"
#include "DeliveryMission.h"

int main() {
    std::cout << "--- Mission Control Simulator Initialized ---" << std::endl;

    MissionQueue missionQueue;

    std::cout << "Adding missions to the queue..." << std::endl;
    missionQueue.addMission(std::make_unique<SurveillanceMission>(101, 2, 34.0, -118.2));  // Prio 2
    missionQueue.addMission(std::make_unique<DeliveryMission>(201, 1, 40.7, -74.0, "Medical Supplies")); // Prio 1
    missionQueue.addMission(std::make_unique<SurveillanceMission>(102, 3, 37.7, -122.4));
    missionQueue.addMission(std::make_unique<DeliveryMission>(202, 1, 41.8, -87.6, "Urgent Documents"));

    std::cout << "\n--- Executing missions based on priority ---" << std::endl;

    // Procesar las misiones. La cola las devuelve en orden de prioridad
    while (!missionQueue.isEmpty()) {
        std::unique_ptr<Mission> nextMission = missionQueue.getNextMission();
        
        std::cout << "\nNext mission (ID: " << nextMission->getId() << ", Prioriy: " << nextMission->getPriority() << ") retrieved from queue." << std::endl;

        // Aqui sucede el Polimorfismo. No se necesita saber el tipo de mision, solo necesitamos llamar execute()
        nextMission->execute();
    }

    std::cout << "\nAll missions completed. Mission Control signing off." << std::endl;
    
    return 0;
}