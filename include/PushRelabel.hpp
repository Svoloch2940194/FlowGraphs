#ifndef PUSH_RELABEL_HPP
#define PUSH_RELABEL_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cmath>

using namespace std;

class PushRelabel {
private:
    int n;
    std::vector<std::vector<double>> capacity;
    std::vector<std::vector<double>> flow;
    vector<int> height;
    vector<double> excess;
    queue<int> excess_vertices;
    std::vector<int> seen;
    
    void push(int u, int v);
    void relabel(int u);
    void discharge(int u);

public:
    PushRelabel(const vector<vector<pair<int, double>>> &adjList);
    double maxFlow(int s, int t);
};

#endif //PUSH_RELABEL_HPP