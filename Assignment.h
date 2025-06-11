#pragma once

#include <vector>
#include "CargoList.h"
#include "FreightList.h"

class Assignment
{
private:
	CargoList assignedCargo;
	FreightList assignedFreight;
	std::vector<std::pair<Cargo, Freight>> assigned;										//vector to store freight and cargo already assigned.

public:
	Assignment(const CargoList& c, const FreightList& f) : assignedCargo(c), assignedFreight(f){}					// constructor
	std::vector<std::pair<Cargo, Freight>> assignMatching();
	std::vector<std::pair<Cargo, Freight>> getAssignments() const;
};

