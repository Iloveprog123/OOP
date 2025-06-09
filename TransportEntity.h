#pragma once

#include <string>

class TransportEntity
{
private:
	std::string id;
	std::string location;
	std::string time;

public:
	TransportEntity(std::string id, std::string location, std::string time);
	std::string getID();
	std::string getLocation();
	std::string getTime();
	void setID(std::string);
	void setLocation(std::string);
	void setTime(std::string);
};


