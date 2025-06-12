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
	bool editFreight(std::string, std::string, std::string);
	const std::vector<Freight>& getFreight() const;
	bool loadFromFile(std::string);
	bool saveToFile(std::string path = "");
};

