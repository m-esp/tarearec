#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <algorithm>

using AdjacencyList = std::vector<std::vector<std::pair<int, int>>>;

struct DijkstraResult {
    std::vector<int> path;
    int totalCost;
};

DijkstraResult dijkstra(const AdjacencyList &graph, int start, int end) {
    const int INF = std::numeric_limits<int>::max();
    int n = graph.size();
    std::vector<int> dist(n, INF);      // Distancias mínimas
    std::vector<int> prev(n, -1);      // Para reconstruir el camino
    std::vector<bool> visited(n, false);
    dist[start] = 0;

    // Cola de prioridad: {distancia acumulada, nodo actual}
    using PQElement = std::pair<int, int>;
    std::priority_queue<PQElement, std::vector<PQElement>, std::greater<PQElement>> pq;
    pq.emplace(0, start);

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();

        if (visited[currentNode]) continue;
        visited[currentNode] = true;

        for (const auto &neighbor : graph[currentNode]) {
            int neighborNode = neighbor.first;
            int weight = neighbor.second;

            if (currentDist + weight < dist[neighborNode]) {
                dist[neighborNode] = currentDist + weight;
                prev[neighborNode] = currentNode;
                pq.emplace(dist[neighborNode], neighborNode);
            }
        }
    }

    // Reconstruir el camino
    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    // Verificar si hay un camino válido
    if (path.size() == 1 && path[0] != start) {
        path.clear();  // No hay camino
        return {path, -1};
    }

    return {path, dist[end]};
}

#endif
