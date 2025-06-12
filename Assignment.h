#pragma once

#include <vector>
#include "CargoList.h"
#include "FreightList.h"

class Scheduler;

class Assignment
{
	friend class Scheduler;

private:
	CargoList* cargo;
	FreightList* freight;											//vector to store freight and cargo already assigned.
	std::vector<std::pair<Cargo*, Freight*>> assignments;							//stores the pairing

public:
	Assignment(CargoList* c, FreightList* f) : cargo(c), freight(f){}					// constructor
	CargoList* getCargo() const;
	FreightList* getFreight() const;
};

