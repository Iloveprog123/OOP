#pragma once

#include <vector>
#include <string>
#include "Freight.h"

class FreightList
{
private:
	std::vector<Freight&> freights;

public:
	void addFreight(Freight&);
	void deleteFreight(std::string);
	void editFreight(std::string, std::string, int);
	std::vector<Freight&> getFreight();
	void loadFromFile(std::string);
	void saveToFile(std::string);
};

