#include "Cargo.h"
#include <iostream>

using namespace std;

void Cargo::printDetails() const{
	cout << "[CARGO]";
	TransportEntity::printDetails();
}
