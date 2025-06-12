#include "Assignment.h"
#include <vector>

using namespace std;

CargoList* Assignment::getCargo() const{
	return cargo;
}

FreightList* Assignment::getFreight() const {
	return freight;
}
