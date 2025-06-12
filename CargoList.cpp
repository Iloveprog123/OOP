#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "CargoList.h"

using namespace std;

bool CargoList::loadFromFile(string path) {
	ifstream inputFile(path);																//open text file

	if (!inputFile.is_open()) {																// error and return false if cannot open file
		cerr << "Error opening file!" << endl;
		return false;
	}

	string line;

	while (getline(inputFile, line)) {														//extract data from text file
		stringstream ss(line);
		string id, location, time;

		if (getline(ss, id, ',') && getline(ss, location, ',') && getline(ss, time, ',')) {		//create Freight object using extracted data
			Cargo c(id, location, time);
			cargos.push_back(c);
		}
	}

	inputFile.close();
	filePath = path;
	return true;
}

bool CargoList::saveToFile(string path) {

	filePath = path.empty() ? filePath : path;

	if (filePath.empty()) {
		std::cerr << "No file path specified!" << std::endl;
		return false;
	}

	ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		cerr << "Error saving file!" << endl;
		return false;
	}

	for (auto cargo : cargos) {
		outputFile << cargo.getID() << "," << cargo.getLocation() << "," << cargo.getTime() << "\n";				//loop through cargo vector and save all updated attributes
	}

		outputFile.close();
		return true;
}

bool CargoList::addCargo(Cargo cargo) {
	for (auto existing : cargos) {
		if (existing.getID() == cargo.getID()) {											//check for duplicate ID and return false to show failure
			return false;
		}
	}

	cargos.push_back(cargo);
	return true;
}

bool CargoList::deleteCargo(string id) {
	for (auto cargoID = cargos.begin(); cargoID != cargos.end(); cargoID++) {
		if (cargoID->getID() == id) {														//loop through cargo vector until ID match
			cargos.erase(cargoID);
			return true;
		}
	}
	return false;
}

bool CargoList::editCargo(string id, string location, string time) {
	for (auto cargo : cargos) {															//loop through cargo vector until ID match
		if (cargo.getID() == id) {
			cargo.setLocation(location);
			cargo.setTime(time);
			return true;
		}
	}
	return false;
}

const vector<Cargo>& CargoList::getCargo() const{
	return cargos;
}