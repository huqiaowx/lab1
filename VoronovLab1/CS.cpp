#include "CS.h"
#include <stdexcept>

int CS::nextId = 1;

CS::CS()
    : id(nextId++), name(""), workshop(0), w_work(0), class_cs(0.0) {
}

CS::CS(const std::string& name, int workshop, int w_work, double class_cs)
    : id(nextId++), name(name), workshop(workshop), w_work(w_work), class_cs(class_cs) {
    if (w_work > workshop) {
        this->w_work = workshop;
    }
}

void CS::setWorkshop(int total) {
    if (total < 0) throw std::invalid_argument("Total workshops cannot be negative");
    workshop = total;
    if (w_work > workshop) {
        w_work = workshop;
    }
}

void CS::setW_work(int working) {
    if (working < 0) throw std::invalid_argument("Working workshops cannot be negative");
    if (working > workshop) throw std::invalid_argument("Working workshops cannot exceed total workshops");
    w_work = working;
}

bool CS::startWorkshop() {
    if (w_work < workshop) {
        w_work++;
        return true;
    }
    return false;
}

bool CS::stopWorkshop() {
    if (w_work > 0) {
        w_work--;
        return true;
    }
    return false;
}

void CS::displayInfo() const {
    std::cout << "Compressor Station ID: " << id << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Total workshops: " << workshop << std::endl;
    std::cout << "Working workshops: " << w_work << std::endl;
    std::cout << "Idle workshops: " << getIdleWorkshops() << std::endl;
    std::cout << "Idle percentage: " << getIdlePercentage() << "%" << std::endl;
    std::cout << "Class: " << class_cs << std::endl;
    std::cout << std::endl;
}