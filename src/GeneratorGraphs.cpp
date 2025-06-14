#include "GeneratorGraphs.hpp"
#include <iostream>

using namespace std;

GraphGenerator::GraphGenerator(int n)
    : numVertices(n),
      dist(0.0, 1.0),
      wdist(0.1, 10.0) {
    random_device rd;
    gen = default_random_engine(rd());
}

int GraphGenerator::getNumVertices() const {
    return numVertices;
}

WeightedGraph GraphGenerator::createEmptyWeightedGraph() const {
    return WeightedGraph(numVertices);
}

WeightedGraph GraphGenerator::completeGraph(bool weighted, bool directed) const {
    WeightedGraph graph = createEmptyWeightedGraph();
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i != j) {
                double weight = weighted ? wdist(gen) : 1.0;
                graph[i].emplace_back(j, weight);
                if (!directed) {
                    graph[j].emplace_back(i, weight);
                }
            }
        }
    }
    return graph;
}

WeightedGraph GraphGenerator::randomGraph(double p, bool weighted, bool directed) const {
    WeightedGraph graph = createEmptyWeightedGraph();
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            if (i != j && dist(gen) < p) {
                double weight = weighted ? wdist(gen) : 1.0;
                graph[i].emplace_back(j, weight);
                if (!directed) {
                    graph[j].emplace_back(i, weight);
                }
            }
        }
    }
    return graph;
}

WeightedGraph GraphGenerator::sparseGraph(bool weighted, bool directed) const {
    return randomGraph(0.1, weighted, directed);
}

WeightedGraph GraphGenerator::denseGraph(bool weighted, bool directed) const {
    return randomGraph(0.8, weighted, directed);
}

WeightedGraph GraphGenerator::starTree(bool weighted, bool directed) const {
    WeightedGraph graph = createEmptyWeightedGraph();
    for (int i = 1; i < numVertices; ++i) {
        double weight = weighted ? wdist(gen) : 1.0;
        graph[0].emplace_back(i, weight);
        if (!directed) {
            graph[i].emplace_back(0, weight);
        }
    }
    return graph;
}

WeightedGraph GraphGenerator::cycleGraph(bool weighted, bool directed) const {
    WeightedGraph graph = createEmptyWeightedGraph();
    for (int i = 0; i < numVertices; ++i) {
        int next = (i + 1) % numVertices;
        double weight = weighted ? wdist(gen) : 1.0;
        graph[i].emplace_back(next, weight);
        if (!directed) {
            graph[next].emplace_back(i, weight);
        }
    }
    return graph;
}

WeightedGraph GraphGenerator::linearGraph(bool weighted, bool directed) const {
    WeightedGraph graph = createEmptyWeightedGraph();
    for (int i = 0; i < numVertices - 1; ++i) {
        double weight = weighted ? wdist(gen) : 1.0;
        graph[i].emplace_back(i + 1, weight);
        if (!directed) {
            graph[i + 1].emplace_back(i, weight);
        }
    }
    return graph;
}

void GraphGenerator::printGraph(const WeightedGraph& graph, int n, const string& title) {
    cout << "=== " << title << " ===" << endl;
    for (int u = 0; u < n; ++u) {
        cout << u << ": ";
        for (const auto& [v, w] : graph[u]) {
            cout << "(" << v << ", " << w << ") ";
        }
        cout << endl;
    }
    cout << endl;
}