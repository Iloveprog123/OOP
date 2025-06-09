#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "FreightList.h"

using namespace std;

void FreightList::loadFromFile(string x) {
	ifstream inputFile(x);				//open text file

	if (!inputFile.is_open()) {			// error if cannot open file
		cerr << "Error opening file!" << endl;
	}

	string line;

	while (getline(inputFile, line)) {		//extract data from text file
		stringstream ss(line);
		string id, location, time;
	}
}

void FreightList::addFreight(Freight&) {

}