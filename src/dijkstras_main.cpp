#include "dijkstras.h"

string file_name = "/home/emmath/ics46/ics-46-hw-9-oimawin/src/small.txt";
int main() {
    Graph G;
    file_to_graph(file_name, G);
    vector<int> previous(G.numVertices, UNDEFINED);
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for (int i = 0; i < G.numVertices; ++i)
        print_path(extract_shortest_path(distances, previous, i), distances[i]);
    return 0;
}