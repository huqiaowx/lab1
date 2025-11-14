#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "PipeManager.h"
#include "CSManager.h"

class Network {
private:
    std::unordered_map<int, std::unordered_map<int, int>> graph;
    std::unordered_map<int, std::unordered_map<int, bool>> freePipesByDiameter;

public:
    Network();

    void addPipe(const Pipe& pipe);
    void addCS(const CS& cs);
    bool connectCS(int csInId, int csOutId, int diameter, PipeManager& pipeManager);
    bool disconnectPipe(int pipeId);
    bool isValidConnection(int csInId, int csOutId) const;
    void displayNetwork() const;
    std::unordered_map<int, int> topologicalSort() const;
    void removeCS(int csId, PipeManager& pipeManager);
    void removePipe(int pipeId);
    bool isEmpty() const;
    bool hasCycle() const;

private:
    void topologicalSortUtil(int v, std::unordered_map<int, bool>& visited,
        std::unordered_map<int, int>& result, int& index) const;
    bool hasCycleUtil(int v, std::unordered_map<int, bool>& visited,
        std::unordered_map<int, bool>& recStack) const;
};