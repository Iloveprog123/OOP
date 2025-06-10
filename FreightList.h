#pragma once

#include <vector>
#include <string>
#include "Freight.h"

class FreightList
{
private:
	std::vector<Freight&> freights;

public:
	bool addFreight(Freight&);
	bool deleteFreight(std::string);
	bool editFreight(std::string, std::string, std::string);
	std::vector<Freight&> getFreight();
	bool loadFromFile(std::string);
	bool saveToFile(std::string);
};

