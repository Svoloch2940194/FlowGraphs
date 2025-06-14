#include "Dinic.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <limits>
#include <chrono>

using namespace std;
using namespace std::chrono;

Dinic::Dinic(const vector<vector<pair<int, double>>>& inputGraph) : FlowGraphBase(inputGraph) {}

double Dinic::maxFlow(int s, int t) {
    auto start = high_resolution_clock::now();

    double total_flow = 0.0;
    vector<int> level(n), ptr(n);

    while (bfs(s, t, level)) {
        fill(ptr.begin(), ptr.end(), 0);
        double pushed;
        while ((pushed = dfs(s, t, numeric_limits<double>::max(), level, ptr)) > 1e-9)
            total_flow += pushed;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << "[Dinic] Max flow = " << total_flow << ", time = " << duration << " μs\n";
    return total_flow;
}

bool Dinic::bfs(int s, int t, vector<int>& level) {
    fill(level.begin(), level.end(), -1);
    queue<int> q;
    q.push(s);
    level[s] = 0;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, cap] : graph[u]) {
            if (cap > 1e-9 && level[v] == -1) {
                level[v] = level[u] + 1;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

double Dinic::dfs(int u, int t, double flow, vector<int>& level, vector<int>& ptr) {
    if (u == t) return flow;
    for (; ptr[u] < graph[u].size(); ++ptr[u]) {
        auto& [v, cap] = graph[u][ptr[u]];
        if (cap > 1e-9 && level[u] < level[v]) {
            double min_flow = min(flow, cap);
            double pushed = dfs(v, t, min_flow, level, ptr);
            if (pushed > 1e-9) {
                cap -= pushed;
                graph[v][reverseMap[v][u]].second += pushed;
                return pushed;
            }
        }
    }
    return 0.0;
}