#include "PipeManager.h"
#include <fstream>
#include <iostream>

void PipeManager::addPipe(const Pipe& pipe) {
    pipes[pipe.getId()] = pipe;
}

Pipe& PipeManager::createPipe() {
    int newId = Pipe::getNextId();
    Pipe& pipe = pipes[newId];
    std::cin >> pipe;
    return pipe;
}

bool PipeManager::deletePipe(int id) {
    return pipes.erase(id) > 0;
}

void PipeManager::deletePipes(const std::vector<int>& ids) {
    for (int id : ids) {
        pipes.erase(id);
    }
}

Pipe* PipeManager::getPipe(int id) {
    auto it = pipes.find(id);
    return (it != pipes.end()) ? &it->second : nullptr;
}

void PipeManager::displayAllPipes() const {
    if (pipes.empty()) {
        std::cout << "No pipes available." << std::endl;
        return;
    }
    for (const auto& entry : pipes) { 
        std::cout << entry.second;
    }
}

void PipeManager::displayPipes(const std::vector<int>& ids) const {
    for (int id : ids) {
        auto it = pipes.find(id);
        if (it != pipes.end()) {
            std::cout << it->second;
        }
    }
}

std::vector<int> PipeManager::getAllIds() const {
    std::vector<int> ids;
    for (const auto& entry : pipes) { 
        ids.push_back(entry.first);
    }
    return ids;
}

void PipeManager::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file for writing!" << std::endl;
        return;
    }

    for (const auto& entry : pipes) {  
        file << entry.second;
    }

    file.close();
    std::cout << "Pipes saved to " << filename << std::endl;
}

void PipeManager::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for reading!" << std::endl;
        return;
    }

    pipes.clear();
    Pipe::resetIdCounter();

    std::string line;
    while (getline(file, line)) {
        if (line == "PIPE") {
            Pipe pipe;
            file >> pipe;
            pipes[pipe.getId()] = pipe;
        }
    }

    file.close();
    std::cout << "Pipes loaded from " << filename << std::endl;
}

bool PipeManager::editPipe(int id) {
    Pipe* pipe = getPipe(id);
    if (!pipe) return false;

    return true;
}

void PipeManager::batchEditPipes(const std::vector<int>& ids) {
    if (ids.empty()) {
        std::cout << "No pipes selected for batch editing." << std::endl;
        return;
    }

    std::cout << "Selected " << ids.size() << " pipes for batch editing:" << std::endl;
    displayPipes(ids);

    std::cout << "Choose action:\n1. Toggle repair status\n2. Change name\n3. Delete pipes\nChoice: ";

    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1: {
        for (int id : ids) {
            Pipe* pipe = getPipe(id);
            if (pipe) {
                pipe->toggleRepair();
                std::cout << "Pipe ID " << id << " repair status toggled to: "
                    << (pipe->getRepair() ? "Under repair" : "Operational") << std::endl;
            }
        }
        std::cout << "Repair status toggled for " << ids.size() << " pipes." << std::endl;
        break;
    }
    case 2: {
        std::cout << "Enter new name for all pipes: ";
        std::string newName;
        std::getline(std::cin, newName);

        for (int id : ids) {
            Pipe* pipe = getPipe(id);
            if (pipe) {
                pipe->setName(newName);
                std::cout << "Pipe ID " << id << " name updated to: " << newName << std::endl;
            }
        }
        std::cout << "Name updated for " << ids.size() << " pipes." << std::endl;
        break;
    }
    case 3: {
        deletePipes(ids);
        std::cout << "Deleted " << ids.size() << " pipes." << std::endl;
        break;
    }
    default:
        std::cout << "Invalid choice." << std::endl;
    }
}