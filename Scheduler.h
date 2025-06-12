#pragma once
#include "Assignment.h"
#include <vector>

class Scheduler {
private:
    Assignment* currentAssignment;

    bool isAssigned(const Cargo* cargo) const;
    bool isAssigned(const Freight* freight) const;

public:
    explicit Scheduler(Assignment* assignment) : currentAssignment(assignment) {}

    void generateSchedule();
    void addPairing(Cargo* c, Freight* f);
    void clearAssignments();

    bool isCargoAssigned(const Cargo* cargo) const;
    bool isFreightAssigned(const Freight* freight) const;
    std::vector<Cargo*> getUnassignedCargo() const;
    std::vector<Freight*> getUnassignedFreight() const;
    const std::vector<std::pair<Cargo*, Freight*>>& getAssignments() const;
};
