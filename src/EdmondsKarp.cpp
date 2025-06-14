#include "EdmondsKarp.hpp"

#include <queue>

using namespace std;
using namespace std::chrono;

EdmondsKarp::EdmondsKarp(const vector<vector<pair<int, double>>>& inputGraph) : FlowGraphBase(inputGraph) {}

double EdmondsKarp::maxFlow(int s, int t) {
    auto start = high_resolution_clock::now();

    double max_flow = 0.0;
    vector<int> parent(n, -1);

    while (bfs(s, t, parent)) {
        double path_flow = numeric_limits<double>::max();

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, getCapacity(u, v));
        }

        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            double flow = path_flow;
            updateEdge(u, v, -flow);
            updateEdge(v, u, flow);
        }

        max_flow += path_flow;
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << "[Edmonds-Karp] Max flow = " << max_flow << ", time = " << duration << " μs\n";
    return max_flow;
}

bool EdmondsKarp::bfs(int s, int t, vector<int>& parent) {
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& [v, cap] : graph[u]) {
            if (!visited[v] && cap > 1e-9) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
                if (v == t) return true;
            }
        }
    }
    return false;
}

double EdmondsKarp::getCapacity(int u, int v) {
    int idx = reverseMap[u][v];
    return graph[u][idx].second;
}

void EdmondsKarp::updateEdge(int u, int v, double delta) {
    int idx = reverseMap[u][v];
    graph[u][idx].second += delta;
}