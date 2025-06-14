#ifndef DINIC_HPP
#define DINIC_HPP

#include "FlowGraphBase.hpp"

class Dinic : public FlowGraphBase {
    bool bfs(int s, int t, std::vector<int>& level);
    double dfs(int u, int t, double flow, std::vector<int>& level, std::vector<int>& ptr);
public:
    explicit Dinic(const std::vector<std::vector<std::pair<int, double>>>& inputGraph);

    double maxFlow(int s, int t) override;
};

#endif //DINIC_HPP