#include "Freight.h"
#include <iostream>
using namespace std;

void Freight::printDetails() const {
	cout << "[FREIGHT]";
	TransportEntity::printDetails();
}