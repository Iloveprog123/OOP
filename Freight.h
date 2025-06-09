#pragma once
#include "TransportEntity.h"

class Freight :
    public TransportEntity
{
public:
    Freight(std::string id, std::string location, std::string time) : TransportEntity(id, location, time){}         //constructor
};

