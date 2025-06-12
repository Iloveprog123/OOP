#pragma once
#include "TransportEntity.h"

class Cargo :
    public TransportEntity
{
public:
    Cargo(std::string id, std::string location, std::string time) : TransportEntity(id, location, time) {}      //constructor
    void printDetails() const;
};

