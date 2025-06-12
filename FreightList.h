#pragma once

#include <vector>
#include <string>
#include "Freight.h"

class FreightList
{
private:
	std::vector<Freight> freights;
	std::string filePath;

public:
	bool addFreight(Freight);
	bool deleteFreight(std::string);
	bool editFreight(std::string id, std::string location, std::string time);
	// bool editFreight(std::string id, std::string location); // Updates only location
	// bool editFreight(std::string id, std::string time);     // Updates only time
	const std::vector<Freight>& getFreight() const;
	bool loadFromFile(std::string);
	bool saveToFile(std::string path = "");
};

