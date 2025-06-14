#include "PushRelabel.hpp"
#include <iostream>
#include <queue>
#include <chrono>

using namespace std;
using namespace std::chrono;

PushRelabel::PushRelabel(const vector<vector<pair<int, double>>>& g) {
    n = static_cast<int>(g.size());
    capacity.resize(n, std::vector<double>(n));
    flow.resize(n, std::vector<double>(n));
    height.resize(n, 0);
    excess.resize(n, 0.0);
    seen.resize(n, 0);
    for(size_t i=0;i<n; ++i) {
        for(auto [v, u]: g[i]) {
            capacity[i][v] = u;
        }
    }
}

void PushRelabel::push(int u, int v) {
    double d = min(excess[u], capacity[u][v] - flow[u][v]);
    flow[u][v] += d;
    flow[v][u] -= d;
    excess[u] -= d;
    excess[v] += d;
    if (d && excess[v] == d)
        excess_vertices.push(v);
}

void PushRelabel::relabel(int u) {
    int d = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++) {
        if (capacity[u][i] - flow[u][i] > 1e-9)
            d = min(d, height[i]);
    }
    if (d < std::numeric_limits<int>::max())
        height[u] = d + 1;
}

void PushRelabel::discharge(int u) {
    while (excess[u] > 0) {
        if (seen[u] < n) {
            int v = seen[u];
            if (capacity[u][v] - flow[u][v] > 1e-9 && height[u] > height[v])
                push(u, v);
            else 
                seen[u]++;
        } else {
            relabel(u);
            seen[u] = 0;
        }
    }
}

double PushRelabel::maxFlow(int s, int t) {
    auto start = high_resolution_clock::now();
    height[s] = n;
    excess[s] = std::numeric_limits<double>::max();
    for (int i = 0; i < n; i++) {
        if (i != s)
            push(s, i);
    }

    while (!excess_vertices.empty()) {
        int u = excess_vertices.front();
        excess_vertices.pop();
        if (u != s && u != t)
            discharge(u);
    }

    double max_flow = 0;
    for (int i = 0; i < n; i++)
        max_flow += flow[i][t];
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    cout << "[Push-Relabel] Max flow = " << max_flow << ", time = " << duration << " μs\n";
    return max_flow;
}