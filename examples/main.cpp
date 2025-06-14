#include "GeneratorGraphs.hpp"
#include "Dinic.hpp"
#include "EdmondsKarp.hpp"
#include "FordFulkerson.hpp"
#include "PushRelabel.hpp"

using namespace std;

int main() {
    int n = 2000;
    GraphGenerator generator(n);
    vector<vector<pair<int, double>>> inputGraph = generator.sparseGraph(true, true);

    cout << "=== Сравнение алгоритмов ===\n";
    // EdmondsKarp ek(inputGraph);
    // ek.maxFlow(0, n-1);
    Dinic dinic(inputGraph);
    dinic.maxFlow(0, n-1);
    // FordFulkerson ff(inputGraph);
    // ff.maxFlow(0, n-1);
    PushRelabel pr(inputGraph);
    pr.maxFlow(0, n-1);
    return 0;

}