#include "MissionControl.h"
#include <iostream>

MissionControl::MissionControl(int fleet_size) {
    for (int i=1; i <= fleet_size; ++i) {
        fleet.push_back(std::make_unique<Drone>(i, mission_queue, stop_signal));
    }
}

MissionControl::~MissionControl() {
    std::cout << "Mission Control shutting down. Signalling drone to stop..." << std::endl;
    stop_signal = true;  // Se manda la señal de parada a todos los drones
}

void MissionControl::addMission(std::shared_ptr<Mission> mission) {
    mission_queue.addMission(std::move(mission));
}

void MissionControl::runSimulation() {
    std::cout << "Fleet of " << fleet.size() << " drones deployed. Main thread is standing by." << std::endl;
    std::cout << "Press Enter to stop the simulation and shut down the drones." << std::endl;
    std::cin.get();
}