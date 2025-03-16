#include "dijkstras.h"

struct CompareSecond {
    bool operator()(const pair<int, int> & a, const pair<int, int> & b) const {
        return a.second > b.second;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    distances[source] = 0;
    previous[source] = UNDEFINED;
    priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> minHeap;
    minHeap.push({source, 0});
    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();
        if (visited[u]) continue;
        visited[u] = true;
        for (Edge edge: G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    stack<int> path;
    int curr = destination;
    path.push(destination);
    for (int prev = previous[destination]; prev != -1; prev = previous[prev]) {
        path.push(prev);
        curr = prev;
    }
    vector<int> result;
    while (!path.empty()) {
        result.push_back(path.top());
        path.pop();
    }
    return result;
}

void print_path(const vector<int>& v, int total) {
    for (int i : v)
        cout << i << " ";
    cout << endl << "Total cost is " << total << endl;
}