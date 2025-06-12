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
	bool editCargo(std::string, std::string, std::string);
	const std::vector<Cargo>& getCargo() const;
	bool loadFromFile(std::string);
	bool saveToFile(std::string path = "");
};

