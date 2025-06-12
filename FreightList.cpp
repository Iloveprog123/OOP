#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include "FreightList.h"

using namespace std;

bool FreightList::loadFromFile(string path) {
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
			Freight f(id, location, time);
			freights.push_back(f);
		}
	}

	inputFile.close();

	filePath = path;
	return true;
}

bool FreightList::saveToFile(string path) {

	filePath = path.empty() ? filePath : path;

	if (filePath.empty()) {
		cerr << "No file path specified!" << endl;
		return false;
	}

	ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		cerr << "Error saving file!" << endl;
		return false;
	}

	for (auto freight : freights) {
		outputFile << freight.getID() << "," << freight.getLocation() << "," << freight.getTime() << "\n";				//loop through cargo vector and save all updated attributes
	}

	outputFile.close();
	return true;
}


bool FreightList::addFreight(Freight freight) {
	for (auto existing : freights) {
		if (existing.getID() == freight.getID()) {											//check for duplicate ID and return false to show failure
			return false;
		}
	}

	freights.push_back(freight);
	return true;
}

bool FreightList::deleteFreight(string id) {
	for (auto freightID = freights.begin(); freightID != freights.end(); freightID++) {
		if (freightID->getID() == id) {														//loop through freight vector until ID match
			freights.erase(freightID);
			return true;
		}
	}
	return false;
}

bool FreightList::editFreight(string id, string location, string time) { // Update all
	for (auto freight : freights) {
		if (freight.getID() == id) {
			freight.setLocation(location);
			freight.setTime(time);
			return true;
		}
	}
	return false;
}

/*bool FreightList::editFreight(string id, string location) { // Only update location
	for (auto& freight : freights) {
		if (freight.getID() == id) {
			freight.setLocation(location);
			return true;
		}
	}
	return false;
}

bool FreightList::editFreight(string id, string time) { // Only update time
	for (auto& freight : freights) {
		if (freight.getID() == id) {
			freight.setTime(time);
			return true;
		}
	}
	return false;
} */

const vector<Freight>& FreightList::getFreight() const {
	return freights;
}
