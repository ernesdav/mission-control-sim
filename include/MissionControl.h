#ifndef MISSION_CONTROL_H
#define MISSION_CONTROL_H

#include "Drone.h"
#include "MissionQueue.h"
#include <vector>
#include <memory>
#include <atomic>

class MissionControl {
private:
    MissionQueue mission_queue;
    std::vector<std::unique_ptr<Drone>> fleet;
    std::atomic<bool> stop_signal{false};
public:
    MissionControl(int fleet_size);
    ~MissionControl();

    void addMission(std::shared_ptr<Mission> mission);
    void runSimulation();
};

#endif