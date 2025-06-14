#ifndef GRAPH_GENERATOR_HPP
#define GRAPH_GENERATOR_HPP

#include <vector>
#include <string>
#include <random>
#include <utility>

using WeightedGraph = std::vector<std::vector<std::pair<int, double>>>;

class GraphGenerator {
private:
    int numVertices;
    mutable std::default_random_engine gen;
    mutable std::uniform_real_distribution<double> dist;
    mutable std::uniform_real_distribution<double> wdist;

    WeightedGraph createEmptyWeightedGraph() const;

public:
    GraphGenerator(int n);

    int getNumVertices() const;

    // Генерация графа с возможностью весов
    WeightedGraph completeGraph(bool weighted = false, bool directed = false) const;
    WeightedGraph randomGraph(double p, bool weighted = false, bool directed = false) const;
    WeightedGraph sparseGraph(bool weighted = false, bool directed = false) const;
    WeightedGraph denseGraph(bool weighted = false, bool directed = false) const;
    WeightedGraph starTree(bool weighted = false, bool directed = false) const;
    WeightedGraph cycleGraph(bool weighted = false, bool directed = false) const;
    WeightedGraph linearGraph(bool weighted = false, bool directed = false) const;

    static void printGraph(const WeightedGraph& graph, int n, const std::string& title);
};

#endif // GRAPH_GENERATOR_HPP