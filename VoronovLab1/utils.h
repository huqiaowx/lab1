#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <functional>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"  

template<typename T>
inline bool inputNumber(T& variable, const std::string& prompt, bool positiveOnly = false) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> variable) {
            if (std::cin.peek() != '\n') {
                std::cout << "Error, please enter only numbers without extra characters." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (positiveOnly && variable <= 0) {
                std::cout << "Error, value must be positive" << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return true;
        }
        else {
            std::cout << "Invalid input, please enter a valid number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

template<typename T>
inline bool inputInRange(T& variable, const std::string& prompt, T minValue, T maxValue) {
    while (true) {
        std::cout << prompt;
        if (std::cin >> variable) {
            if (std::cin.peek() != '\n') {
                std::cout << "Error, please enter only numbers without extra characters." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (variable >= minValue && variable <= maxValue) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
            else {
                std::cout << "Error, value must be between " << minValue << " and " << maxValue << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        else {
            std::cout << "Invalid input, please enter a valid number." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

template<>
inline bool inputInRange<bool>(bool& variable, const std::string& prompt, bool minValue, bool maxValue) {
    int temp;
    while (true) {
        std::cout << prompt;
        if (std::cin >> temp) {
            if (std::cin.peek() != '\n') {
                std::cout << "Error, please enter only 0 or 1 without extra characters." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (temp == 0 || temp == 1) {
                variable = (temp == 1);
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return true;
            }
            else {
                std::cout << "Error, please enter 0 or 1." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
        }
        else {
            std::cout << "Invalid input, please enter 0 or 1." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

template<typename Key, typename Value, typename Predicate>
std::vector<Key> findInMap(const std::unordered_map<Key, Value>& map, Predicate predicate) {
    std::vector<Key> result;
    for (const auto& pair : map) {
        if (predicate(pair.second)) {
            result.push_back(pair.first);
        }
    }
    return result;
}

namespace SearchUtils {
    inline std::vector<int> findPipesByName(const std::unordered_map<int, Pipe>& pipes, const std::string& name) {
        return findInMap(pipes, [&name](const Pipe& pipe) {
            return pipe.getName().find(name) != std::string::npos;
            });
    }

    inline std::vector<int> findPipesByRepairStatus(const std::unordered_map<int, Pipe>& pipes, bool inRepair) {
        return findInMap(pipes, [inRepair](const Pipe& pipe) {
            return pipe.getRepair() == inRepair;
            });
    }

    inline std::vector<int> findCSsByName(const std::unordered_map<int, CS>& stations, const std::string& name) {
        return findInMap(stations, [&name](const CS& cs) {
            return cs.getName().find(name) != std::string::npos;
            });
    }

    inline std::vector<int> findCSsByIdlePercentage(const std::unordered_map<int, CS>& stations, double minPercent, double maxPercent = 100.0) {
        return findInMap(stations, [minPercent, maxPercent](const CS& cs) {
            double idlePercent = cs.getIdlePercentage();
            return idlePercent >= minPercent && idlePercent <= maxPercent;
            });
    }
}