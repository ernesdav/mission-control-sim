#ifndef SURVEILLANCE_MISSION_H
#define SURVEILLANCE_MISSION_H

#include "Mission.h"

class SurveillanceMission : public Mission {
private:
    double area_center_x;
    double area_center_y;
public:
    SurveillanceMission(int id, int priority, double x, double y);

    // Sobrescribimos la función execute de la clase base.
    void execute() const override;
};

#endif