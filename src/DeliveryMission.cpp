#include "DeliveryMission.h"
#include <iostream>
#include <chrono>
#include <thread>

DeliveryMission::DeliveryMission(int id, int priority, double dest_x, double dest_y, const std::string& item_name)
    : Mission(id, priority), destination_x(dest_x), destination_y(dest_y), item(item_name) {}

void DeliveryMission::execute() const {
    std::cout   << "Executing Delivery Mission " << missionId
                << ": Delivering item '" << item << "' to ("
                << destination_x << ", " << destination_y << ")..." << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Delivery Mission " << missionId << " completed." << std::endl;
}

