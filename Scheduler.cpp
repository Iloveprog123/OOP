#include "Scheduler.h"

void Scheduler::generateSchedule() {
    currentAssignment->assignments.clear();

    // Get references to persistent objects
    const auto& cargos = currentAssignment->getCargo()->getCargo();
    const auto& freights = currentAssignment->getFreight()->getFreight();

    for (const auto& cargo : cargos) {
        for (const auto& freight : freights) {
            if (cargo.getLocation() == freight.getLocation() &&
                cargo.getTime() == freight.getTime()) {
                // Store pointers to the persistent objects
                currentAssignment->assignments.emplace_back(
                    &const_cast<Cargo&>(cargo),
                    &const_cast<Freight&>(freight)
                );
            }
        }
    }
}


void Scheduler::addPairing(Cargo* c, Freight* f) {
    if (!isAssigned(c) && !isAssigned(f)) {
        currentAssignment->assignments.emplace_back(c, f);
    }
}

void Scheduler::clearAssignments() {
    currentAssignment->assignments.clear();
}

bool Scheduler::isAssigned(const Cargo* cargo) const {
    for (const auto& pair : currentAssignment->assignments) {
        if (pair.first == cargo) return true;
    }
    return false;
}

bool Scheduler::isAssigned(const Freight* freight) const {
    for (const auto& pair : currentAssignment->assignments) {
        if (pair.second == freight) return true;
    }
    return false;
}

bool Scheduler::isCargoAssigned(const Cargo* cargo) const {
    return isAssigned(cargo);
}

bool Scheduler::isFreightAssigned(const Freight* freight) const {
    return isAssigned(freight);
}

std::vector<Cargo*> Scheduler::getUnassignedCargo() const {
    std::vector<Cargo*> unassigned;
    const auto& cargos = currentAssignment->getCargo()->getCargo();
    for (const auto& cargo : cargos) {
        if (!isAssigned(&cargo)) {
            unassigned.push_back(&const_cast<Cargo&>(cargo));
        }
    }
    return unassigned;
}

std::vector<Freight*> Scheduler::getUnassignedFreight() const {
    std::vector<Freight*> unassigned;
    const auto& freights = currentAssignment->getFreight()->getFreight();
    for (const auto& freight : freights) {
        if (!isAssigned(&freight)) {
            unassigned.push_back(&const_cast<Freight&>(freight));
        }
    }
    return unassigned;
}

const std::vector<std::pair<Cargo*, Freight*>>& Scheduler::getAssignments() const {
    return currentAssignment->assignments;
}
