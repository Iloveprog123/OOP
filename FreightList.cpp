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
	return true;
}

bool FreightList::saveToFile(string path) {
	ofstream outputFile(path);

	if (!outputFile.is_open()) {															//error if unable to open file to save
		cerr << "Error saving file!" << endl;
		return false;
	}

	for (auto freight : freights) {
		outputFile << freight.getID() << "," << freight.getLocation() << "," << freight.getTime() << "\n";				//loop through freight vector and save all updated attributes
	}

	outputFile.close();
	return true;
}

bool FreightList::addFreight(Freight& freight) {
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

bool FreightList::editFreight(string id, string location, string time) {
	for (auto freight : freights) {															//loop through freight vector until ID match
		if (freight.getID() == id) {
			freight.setLocation(location);
			freight.setTime(time);
			return true;
		}
	}
	return false;
}

vector<Freight&> FreightList::getFreight() {
	return freights;
}
