#include "Network.h"
#include <iostream>
#include <unordered_set>
#include <queue>

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

    std::unordered_set<int> allVertices;

    for (const auto& vertex : graph) {
        for (const auto& neighbor : vertex.second) {
            allVertices.insert(vertex.first);
            allVertices.insert(neighbor.first);
        }
    }

    if (allVertices.empty()) {
        return result;
    }

    std::unordered_set<int> sources = allVertices;

    for (const auto& vertex : graph) {
        for (const auto& neighbor : vertex.second) {
            sources.erase(neighbor.first);
        }
    }

    if (sources.empty()) {
        std::cout << "No source vertices found." << std::endl;
        return result;
    }

    for (int v : sources) {
        if (!visited[v]) {
            topologicalSortUtil(v, visited, result, index);
        }
    }

    std::unordered_map<int, int> correctOrder;
    for (int i = 0; i < index; i++) {
        correctOrder[i] = result[index - 1 - i];
    }

    return correctOrder;
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

bool Network::hasCSConnections(int csId) const {
    if (graph.find(csId) != graph.end() && !graph.at(csId).empty()) {
        return true;
    }
    for (const auto& csIn : graph) {
        if (csIn.second.find(csId) != csIn.second.end()) {
            return true;
        }
    }
    return false;
}

bool Network::hasPipeConnections(int pipeId) const {
    for (const auto& csIn : graph) {
        for (const auto& csOut : csIn.second) {
            if (csOut.second == pipeId) {
                return true;
            }
        }
    }
    return false;
}

bool Network::removeCS(int csId, PipeManager& pipeManager) {
    std::unordered_set<int> pipesToFree;

    auto outgoingIt = graph.find(csId);
    if (outgoingIt != graph.end()) {
        for (const auto& connection : outgoingIt->second) {
            pipesToFree.insert(connection.second); 
        }
    }

    for (auto& csIn : graph) {
        auto it = csIn.second.find(csId);
        if (it != csIn.second.end()) {
            pipesToFree.insert(it->second); 
            csIn.second.erase(it);
        }
    }

    for (int pipeId : pipesToFree) {
        Pipe* pipe = pipeManager.getPipe(pipeId);
        if (pipe) {
            freePipesByDiameter[pipe->getDiametr()][pipeId] = true;
        }
    }

    graph.erase(csId);
    return 1;
}

bool Network::removePipe(int pipeId, PipeManager& pipeManager, bool returnToFree = false) {
    bool found = false;

    for (auto& csIn : graph) {
        for (auto it = csIn.second.begin(); it != csIn.second.end(); ) {
            if (it->second == pipeId) {
                if (returnToFree) {
                    Pipe* pipe = pipeManager.getPipe(pipeId);
                    if (pipe) {
                        freePipesByDiameter[pipe->getDiametr()][pipeId] = true;
                    }
                }

                it = csIn.second.erase(it);
                found = true;
            }
            else {
                ++it;
            }
        }
    }

    if (found) {
        std::cout << "Pipe " << pipeId << " removed from network and returned to free pipes!" << std::endl;
        return 1;
    }
    else {
        std::cout << "Pipe " << pipeId << " not found in network connections!" << std::endl;
        return 0;
    }
}

double Network::findMaxFlow(int sourceId, int sinkId, PipeManager& pipeManager) {
    if (graph.empty()) {
        std::cout << "Network is empty, nothing to calculate." << std::endl;
        return 0.0;
    }

    bool foundSource = false;
    bool foundSink = false;

    for (const auto& node : graph) {
        if (node.first == sourceId) foundSource = true;
        if (node.first == sinkId) foundSink = true;
        for (const auto& neighbor : node.second) {
            if (neighbor.first == sinkId) foundSink = true;
        }
    }

    if (!foundSource || !foundSink) {
        std::cout << "Error: Source or sink stations not found in the network." << std::endl;
        return 0.0;
    }

    std::unordered_map<int, std::unordered_map<int, double>> residual;

    for (const auto& from : graph) {
        for (const auto& to : from.second) {
            Pipe* pipe = pipeManager.getPipe(to.second);
            if (pipe) {
                residual[from.first][to.first] = pipe->getCapacity();
            }
        }
    }

    double maxFlow = 0.0;
    int iteration = 0;

    while (true) {
        iteration++;

        std::unordered_map<int, int> parent;
        std::queue<int> q;
        q.push(sourceId);
        parent[sourceId] = -1;

        bool foundPath = false;

        while (!q.empty() && !foundPath) {
            int u = q.front();
            q.pop();

            auto it = residual.find(u);
            if (it != residual.end()) {
                for (const auto& v : it->second) {
                    if (parent.find(v.first) == parent.end() && v.second > 0) {
                        parent[v.first] = u;
                        if (v.first == sinkId) {
                            foundPath = true;
                            break;
                        }
                        q.push(v.first);
                    }
                }
            }
        }

        if (!foundPath) {
            std::cout << "Iteration " << iteration << ": No more augmenting paths found." << std::endl;
            break;
        }

        double pathFlow = std::numeric_limits<double>::max();
        for (int v = sinkId; v != sourceId; v = parent[v]) {
            int u = parent[v];
            pathFlow = std::min(pathFlow, residual[u][v]);
        }

        std::cout << "Iteration " << iteration << ": Found path with flow = " << pathFlow << std::endl;

        std::cout << "Path: ";
        std::vector<int> path;
        for (int v = sinkId; v != sourceId; v = parent[v]) {
            path.push_back(v);
        }
        path.push_back(sourceId);
        for (int i = path.size() - 1; i >= 0; i--) {
            std::cout << "CS " << path[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;

        for (int v = sinkId; v != sourceId; v = parent[v]) {
            int u = parent[v];
            residual[u][v] -= pathFlow;
        }

        maxFlow += pathFlow;
        std::cout << "Current total flow: " << maxFlow << std::endl << std::endl;
    }

    std::cout << "Maximum flow calculated: " << maxFlow << " units" << std::endl;
    return maxFlow;
}

std::vector<int> Network::findShortestPath(int startId, int endId, PipeManager& pipeManager, double& totalLength) {
    totalLength = 0.0;

    if (graph.empty()) {
        std::cout << "Network is empty, no path to find." << std::endl;
        return {};
    }

    bool foundStart = false;
    bool foundEnd = false;

    for (const auto& node : graph) {
        if (node.first == startId) foundStart = true;
        if (node.first == endId) foundEnd = true;
        for (const auto& neighbor : node.second) {
            if (neighbor.first == endId) foundEnd = true;
        }
    }

    if (!foundStart || !foundEnd) {
        std::cout << "Error: Start or end station not found in the network." << std::endl;
        return {};
    }

    if (startId == endId) {
        std::cout << "Start and end are the same station." << std::endl;
        return { startId };
    }

    std::unordered_map<int, double> dist;
    std::unordered_map<int, int> prev;
    std::unordered_set<int> visited;

    for (const auto& node : graph) {
        dist[node.first] = std::numeric_limits<double>::max();
    }

    for (const auto& node : graph) {
        for (const auto& neighbor : node.second) {
            dist[neighbor.first] = std::numeric_limits<double>::max();
        }
    }

    dist[startId] = 0;

    while (true) {
        int current = -1;
        double minDist = std::numeric_limits<double>::max();

        for (const auto& d : dist) {
            if (!visited.count(d.first) && d.second < minDist) {
                minDist = d.second;
                current = d.first;
            }
        }

        if (current == -1 || current == endId) break;

        visited.insert(current);

        auto it = graph.find(current);
        if (it != graph.end()) {
            for (const auto& neighbor : it->second) {
                if (visited.count(neighbor.first)) continue;

                Pipe* pipe = pipeManager.getPipe(neighbor.second);
                if (!pipe) continue;

                double weight = pipe->getWeight();
                if (weight == std::numeric_limits<double>::max()) {
                    continue;
                }

                if (weight == std::numeric_limits<double>::max()) continue;

                double newDist = dist[current] + weight;
                if (newDist < dist[neighbor.first]) {
                    dist[neighbor.first] = newDist;
                    prev[neighbor.first] = current;
                }
            }
        }
    }

    if (dist[endId] == std::numeric_limits<double>::max()) {
        return {};
    }

    std::vector<int> path;
    for (int at = endId; at != startId; at = prev[at]) {
        path.push_back(at);
    }
    path.push_back(startId);
    std::reverse(path.begin(), path.end());

    totalLength = dist[endId];
    return path;
}