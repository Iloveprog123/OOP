#include "TransportEntity.h"
#include <string>

using namespace std;

string TransportEntity::getID() const{
	return id;
}

string TransportEntity::getLocation() const{
	return location;
}

string TransportEntity::getTime() const{
	return time;
}

void TransportEntity::setID(string x) {
	id = x;
}

void TransportEntity::setLocation(string x) {
	location = x;
}

void TransportEntity::setTime(string x) {
	time = x;
}

TransportEntity::TransportEntity(string id, string location, string time) : id(id), location(location), time(time) {}