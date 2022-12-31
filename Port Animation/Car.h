#pragma once

#include <string>

class Car{

private:
    int capacity;
    std::string arrivalTime;

public:
    int getCapacity();
    std::string getArrivalTime();
};
