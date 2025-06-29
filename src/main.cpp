#include "MissionControl.h"
#include "SurveillanceMission.h"
#include "DeliveryMission.h"
#include <memory>

int main() {
    MissionControl mc(3); // Creamos un centro de control con 3 drones

    // Añadimos misiones al sistema
    mc.addMission(std::make_shared<SurveillanceMission>(101, 2, 34.0, -118.2));
    mc.addMission(std::make_shared<DeliveryMission>(201, 1, 40.7, -74.0, "Medical Supplies"));
    mc.addMission(std::make_shared<SurveillanceMission>(102, 3, 37.7, -122.4));
    mc.addMission(std::make_shared<DeliveryMission>(202, 1, 41.8, -87.6, "Urgent Documents"));
    mc.addMission(std::make_shared<SurveillanceMission>(103, 2, 29.7, -95.3));

    // La simulación se ejecuta hasta que el usuario presione Enter
    mc.runSimulation();

    return 0;
}