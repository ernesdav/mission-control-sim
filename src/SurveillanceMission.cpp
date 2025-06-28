#include "SurveillanceMission.h"
#include <iostream>
#include <chrono>   // Para la simulacion de tiempo
#include <thread>   // Para la simulacion de tiempo

// El constructor llama al constructor de la clase base (Mission) para inicializar id y priority.
SurveillanceMission::SurveillanceMission(int id, int priority, double x, double y)
    : Mission(id, priority), area_center_x(x), area_center_y(y) {}

void SurveillanceMission::execute() const {
    std::cout   << "Executing Surveillance Mission " << missionId
                << ": Surveying area around (" << area_center_x
                << ", " << area_center_y << ")..." << std::endl;

    // Simulamos que la mision toma tiempo
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Surveillance Mission " << missionId << " completed." << std::endl;
}