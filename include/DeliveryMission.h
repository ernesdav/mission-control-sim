#ifndef DELIVERY_MISSION_H
#define DELIVERY_MISSION_H

#include "Mission.h"
#include <string>

class DeliveryMission : public Mission {
private:
    double destination_x;
    double destination_y;
    std::string item;

public:
    DeliveryMission(int id, int priority, double dest_x, double dest_y, const std::string& item_name);

    void execute() const override;
};


#endif