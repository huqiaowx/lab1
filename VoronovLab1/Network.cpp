#include "Network.h"
#include <iostream>

Network::Network() {}

void Network::addPipe(const Pipe& pipe) {
    freePipesByDiameter[pipe.getDiametr()][pipe.getId()] = true;
}

void Network::addCS(const CS& cs) {
    graph[cs.getId()];
}

bool Network::connectCS(int csInId, int csOutId, int diameter, PipeManager& pipeManager) {
    if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        std::cout << "Error: Invalid diameter! Allowed: 500, 700, 1000, 1400" << std::endl;
        return false;
    }

    if (!isValidConnection(csInId, csOutId)) {
        return false;
    }

    auto diamIt = freePipesByDiameter.find(diameter);
    if (diamIt != freePipesByDiameter.end() && !diamIt->second.empty()) {
        std::cout << "Available pipes with diameter " << diameter << ":" << std::endl;
        for (const auto& pipe : diamIt->second) {
            std::cout << "Pipe ID: " << pipe.first << std::endl;
        }

        int selectedPipeId;
        std::cout << "Select pipe ID to use: ";
        std::cin >> selectedPipeId;
        std::cin.ignore();

        if (diamIt->second.find(selectedPipeId) == diamIt->second.end()) {
            std::cout << "Error: Invalid pipe ID or pipe not available!" << std::endl;
            return false;
        }

        diamIt->second.erase(selectedPipeId);
        graph[csInId][csOutId] = selectedPipeId;

        std::cout << "Connected CS " << csInId << " -> CS " << csOutId
            << " using pipe " << selectedPipeId << " (diameter: " << diameter << ")" << std::endl;
        return true;
    }

    std::cout << "No free pipe with diameter " << diameter << ". Creating new pipe..." << std::endl;

    Pipe& newPipe = pipeManager.createPipeWithoutDiameter();
    newPipe.setDiametr(diameter); 

    graph[csInId][csOutId] = newPipe.getId();

    std::cout << "Connected CS " << csInId << " -> CS " << csOutId
        << " using NEW pipe " << newPipe.getId() << " (diameter: " << diameter << ")" << std::endl;
    return true;
}

bool Network::disconnectPipe(int pipeId) {
    for (auto& csIn : graph) {
        for (auto it = csIn.second.begin(); it != csIn.second.end(); ++it) {
            if (it->second == pipeId) {
                csIn.second.erase(it);
                return true;
            }
        }
    }
    return false;
}

bool Network::isValidConnection(int csInId, int csOutId) const {
    if (csInId == csOutId) {
        std::cout << "Error: Cannot connect CS to itself!" << std::endl;
        return false;
    }

    auto csInIt = graph.find(csInId);
    if (csInIt != graph.end() && csInIt->second.find(csOutId) != csInIt->second.end()) {
        std::cout << "Error: Connection already exists!" << std::endl;
        return false;
    }

    auto csOutIt = graph.find(csOutId);
    if (csOutIt != graph.end() && csOutIt->second.find(csInId) != csOutIt->second.end()) {
        std::cout << "Error: Reverse connection exists!" << std::endl;
        return false;
    }

    return true;
}

void Network::displayNetwork() const {
    std::cout << "\n NETWORK " << std::endl;

    bool hasConnections = false;
    for (const auto& csIn : graph) {
        if (!csIn.second.empty()) {
            hasConnections = true;
            std::cout << "CS " << csIn.first << " -> ";
            for (const auto& csOut : csIn.second) {
                std::cout << "CS " << csOut.first << "(pipe:" << csOut.second << ") ";
            }
            std::cout << std::endl;
        }
    }

    if (!hasConnections) {
        std::cout << "No connections in network" << std::endl;
    }
}

std::unordered_map<int, int> Network::topologicalSort() const {
    std::unordered_map<int, int> result;
    std::unordered_map<int, bool> visited;
    int index = 0;

    if (hasCycle()) {
        std::cout << "Error: Graph has cycles, cannot perform topological sort!" << std::endl;
        return result;
    }

    for (const auto& vertex : graph) {
        int v = vertex.first;
        if (!visited[v]) {
            topologicalSortUtil(v, visited, result, index);
        }
    }

    return result;
}

void Network::topologicalSortUtil(int v, std::unordered_map<int, bool>& visited,
    std::unordered_map<int, int>& result, int& index) const {
    visited[v] = true;

    auto it = graph.find(v);
    if (it != graph.end()) {
        for (const auto& adjacent : it->second) {
            int adjacentVertex = adjacent.first;
            if (!visited[adjacentVertex]) {
                topologicalSortUtil(adjacentVertex, visited, result, index);
            }
        }
    }

    result[index++] = v;
}

bool Network::isEmpty() const {
    for (const auto& vertex : graph) {
        if (!vertex.second.empty()) {
            return false;
        }
    }
    return true;
}

bool Network::hasCycle() const {
    std::unordered_map<int, bool> visited;
    std::unordered_map<int, bool> recStack;

    for (const auto& vertex : graph) {
        int v = vertex.first;
        if (!visited[v]) {
            if (hasCycleUtil(v, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool Network::hasCycleUtil(int v, std::unordered_map<int, bool>& visited,
    std::unordered_map<int, bool>& recStack) const {
    if (!visited[v]) {
        visited[v] = true;
        recStack[v] = true;

        auto it = graph.find(v);
        if (it != graph.end()) {
            for (const auto& adjacent : it->second) {
                int adjacentVertex = adjacent.first;
                if (!visited[adjacentVertex] && hasCycleUtil(adjacentVertex, visited, recStack)) {
                    return true;
                }
                else if (recStack[adjacentVertex]) {
                    return true;
                }
            }
        }
    }
    recStack[v] = false;
    return false;
}

void Network::removeCS(int csId) {}
void Network::removePipe(int pipeId) {}