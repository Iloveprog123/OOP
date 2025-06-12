#pragma once

#include <vector>
#include <string>
#include "Cargo.h"

class CargoList
{
private:
	std::vector<Cargo> cargos;
	std::string filePath;

public:
	bool addCargo(Cargo);
	bool deleteCargo(std::string);
	bool editCargo(std::string id, std::string location, std::string time); // Updates all
	//bool editCargo(std::string id, std::string location); // Updates only location
	//bool editCargo(std::string id, std::string time);     // Updates only time
	const std::vector<Cargo>& getCargo() const;
	bool loadFromFile(std::string);
	bool saveToFile(std::string path = "");
};

