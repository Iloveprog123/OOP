#pragma once

#include <string>

class TransportEntity
{
private:
	std::string id;
	std::string location;
	std::string time;

public:
	std::string getID();
	std::string getLocation();
	int getTime();
	void setID(std::string);
	void setLocation(std::string);
	void setTime(std::string);
};


