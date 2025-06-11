#include "Assignment.h"
#include <vector>

using namespace std;

vector<pair<Cargo, Freight>> Assignment::assignMatching() {
	assigned.clear();

	auto cargos = assignedCargo.getCargo();
	auto freights = assignedFreight.getFreight();

	for (const auto& cargo : cargos) {									//loop through cargo vector and freight vector to find matching location & time
		for (const auto& freight : freights) {
			if (cargo.getLocation() == freight.getLocation() && cargo.getTime() == freight.getTime()) {
				assigned.emplace_back(cargo, freight);
			}
		}
	}
	return assigned;
}

vector<pair<Cargo, Freight>> Assignment::getAssignments() const{
	return assigned;
}

