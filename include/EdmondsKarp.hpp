#ifndef EDMONDS_KARP_HPP
#define EDMONDS_KARP_HPP

#include "FlowGraphBase.hpp"

class EdmondsKarp : public FlowGraphBase {
    bool bfs(int s, int t, std::vector<int>& parent);
    double getCapacity(int u, int v);
    void updateEdge(int u, int v, double delta);
public:
    explicit EdmondsKarp(const std::vector<std::vector<std::pair<int, double>>>& inputGraph);
    
    double maxFlow(int s, int t) override;
};

#endif //EDMONDS_KARP_HPP