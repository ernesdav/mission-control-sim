#ifndef MISSION_H
#define MISSION_H

class Mission {
protected:
    int missionId;
    int priority;
public:
    Mission(int id, int prio) : missionId(id), priority(prio) {}
    // Destructor virtual: crucial para clases base.
    virtual ~Mission() = default;

    // Función virtual pura: define la acción de la misión.
    // Las clases hijas DEBEN implementar este método.
    virtual void execute() const = 0;

    int getPriority() const { return priority; }
    int getId() const { return missionId; }
};

#endif