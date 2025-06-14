#include "FordFulkerson.hpp"

using namespace std;
using namespace std::chrono;

FordFulkerson::FordFulkerson(const vector<vector<pair<int, double>>>& inputGraph) : FlowGraphBase(inputGraph) {}

double FordFulkerson::maxFlow(int s, int t) {
    auto start = high_resolution_clock::now();

    double max_flow = 0.0;
    vector<bool> visited(n);

    double path_flow;
    do {
        fill(visited.begin(), visited.end(), false);
        path_flow = dfs(s, t, numeric_limits<double>::max(), visited);
        if (path_flow > 1e-9)
            max_flow += path_flow;
    } while (path_flow > 1e-9);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << "[Ford-Fulkerson] Max flow = " << max_flow << ", time = " << duration << " μs\n";
    return max_flow;
}

double FordFulkerson::dfs(int u, int t, double flow, vector<bool>& visited) {
    if (u == t) return flow;
    visited[u] = true;

    for (auto& [v, cap] : graph[u]) {
        if (!visited[v] && cap > 1e-9) {
            double min_flow = min(flow, cap);
            double res = dfs(v, t, min_flow, visited);
            if (res > 1e-9) {
                cap -= res;
                graph[v][reverseMap[v][u]].second += res;
                return res;
            }
        }
    }
    return 0.0;
}