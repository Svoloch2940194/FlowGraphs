#ifndef FORD_FULKRSON_HPP
#define FORD_FULKRSON_HPP

#include "FlowGraphBase.hpp"

class FordFulkerson : public FlowGraphBase {
    double dfs(int u, int t, double flow, std::vector<bool>& visited);
public:
    explicit FordFulkerson(const std::vector<std::vector<std::pair<int, double>>>& inputGraph);

    double maxFlow(int s, int t) override;
};

#endif // FORD_FULKRSON_HPP