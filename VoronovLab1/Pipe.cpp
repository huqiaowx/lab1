#include "Pipe.h"
#include <iostream>

int Pipe::nextId = 1;

Pipe::Pipe() : id(nextId++), name(""), length(0), diameter(0), inRepair(false) {}

Pipe::Pipe(const std::string& name, double length, int diameter, bool inRepair)
    : id(nextId++), name(name), length(length), diameter(diameter), inRepair(inRepair) {
}

void Pipe::displayInfo() const {
    std::cout << " Pipe ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Length: " << length << std::endl;
    std::cout << "Diameter: " << diameter << std::endl;
    std::cout << "Status: " << (inRepair ? "OPERATIONAL" : "UNDER REPAIR") << std::endl;
    std::cout << std::endl;
}