#pragma once

#include <string>

class Ship{

private:
    int capacity;
    std::string arrivalTime;

public:
    int getCapacity();
    std::string getArrivalTime();
};
