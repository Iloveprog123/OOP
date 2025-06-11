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
	std::string getID() const;
	std::string getLocation() const;
	std::string getTime() const;
	void setID(std::string);
	void setLocation(std::string);
	void setTime(std::string);
};


