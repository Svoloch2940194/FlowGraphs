#ifndef FLOW_GRAPH_BASE_HPP
#define FLOW_GRAPH_BASE_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

class FlowGraphBase {
protected:
    int n;
    using Edge = std::pair<int, double>;
    std::vector<std::vector<Edge>> graph;
    std::vector<std::unordered_map<int, int>> reverseMap;

public:
    FlowGraphBase(const std::vector<std::vector<std::pair<int, double>>>& inputGraph);

    void addEdge(int from, int to, double capacity);
    virtual double maxFlow(int s, int t) = 0;

    virtual ~FlowGraphBase() = default;
};

#endif //FLOW_GRAPH_BASE_HPP