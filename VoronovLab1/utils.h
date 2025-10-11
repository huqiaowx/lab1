#pragma once
#include <iostream>
#include <string>
#include <limits>

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