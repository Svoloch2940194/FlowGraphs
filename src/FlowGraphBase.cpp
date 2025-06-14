#include "FlowGraphBase.hpp"

FlowGraphBase::FlowGraphBase(const vector<vector<pair<int, double>>>& inputGraph) {
    n = inputGraph.size();
    graph.resize(n);
    reverseMap.resize(n);
    
    for (int u = 0; u < n; ++u) {
        for (auto& edge : inputGraph[u]) {
            addEdge(u, edge.first, edge.second);
        }
    }
}

void FlowGraphBase::addEdge(int from, int to, double capacity) {
    if (reverseMap[from].count(to)) {
        graph[from][reverseMap[from][to]].second += capacity;
    } else {
        int idx = graph[from].size();
        graph[from].push_back({to, capacity});
        reverseMap[from][to] = idx;
    }

    if (!reverseMap[to].count(from)) {
        int rev_idx = graph[to].size();
        graph[to].push_back({from, 0.0});
        reverseMap[to][from] = rev_idx;
    }
}