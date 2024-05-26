#include "Algorithms.hpp"

#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

#include "Graph.hpp"

const int BigNum = std::numeric_limits<int>::max();
enum Color { WHITE,
             GRAY,
             BLACK };

using namespace std;

using namespace ariel;
// helper function declaration
vector<vector<size_t>> DFS(const Graph& graph);
vector<size_t> DFS_Visit(const Graph& graph, int vertax, vector<bool>& visited);
void BFS(const Graph& graph, int start,  vector<int>& distance, vector<int>& parent);
string BellmanFord(const Graph& g, int start, int end, vector<int>& distance, vector<int>& parent);
bool dfsVisit(const Graph& g, size_t u, vector<Color>& colors, vector<int>& parent);
//  end function declaration

bool ariel::Algorithms::isConnected(const Graph& g) {
    if (g.getGraph().empty()) {
        return true;
    }

    vector<vector<size_t>> firstDfs = DFS(g);

    if (firstDfs.size() == 1) {  // Means that there is one tree - the graph is directed
        return true;
    }

    // Do second DFS (visit) from the root on the lsat tree
    size_t lastTreeRoot = firstDfs.back().front();

    vector<bool> visited(g.getGraph().size(), false);                // we dont visit in any vertex yet
    vector<size_t> secondDfs = DFS_Visit(g, lastTreeRoot, visited);  // dfs-visit from the root
    return secondDfs.size() == g.getGraph().size();                  // check if dfs-visit discover all the graph
}

std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
    // If the graph is not weighted, use BFS to find the shortest path
    vector<int> distance(g.numVertices(), BigNum);
    vector<int> parent(g.numVertices(), -1);  // This is will be the path that we will print to see the shortest path

    if (!g.getWeighted()) {
        BFS(g, start, distance, parent);
    } else {
        // Use Bellman-Ford
        string ans = BellmanFord(g, start, end, distance, parent);
        if (ans != "1") {  // There is no negative cycle
            return ans;
        }
    }

    if (distance[(size_t)end] == BigNum ) {  // Check if there is a path
        return "-1";
    }

    string path = std::to_string(end);
    int p = parent[(size_t)end];
    while(p!=-1){
        path = std::to_string(p) +"->" + path;
        p = parent[(size_t)p];
    }
    return path;
}

bool Algorithms::isContainsCycle(const Graph& g) {
    vector<int> parent(g.numVertices(), -1); // Initialize parent vector with -1
    vector<Color> colors(g.numVertices(), WHITE); // Initialize colors vector with WHITE
    for (size_t i = 0; i < g.numVertices(); ++i) {
        if (colors[i] == WHITE && dfsVisit(g, i, colors, parent)) {
            return true;
        }
    }
    return false; // No cycle found in the graph
}

bool Algorithms::negativeCycle(const Graph& g) {
    vector<int> distance(g.numVertices(), -1);
    vector<int> parent(g.numVertices(), -1);  // This is will be the path that we will print to see the shortest path

    size_t size = g.getGraph().size();
    vector<vector<int>> tempMat(size + 1, vector<int>(size + 1, BigNum));  // New mat. on here we will do bellman ford
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (g.getGraph()[i][j] == 0) {
                tempMat[i][j] = g.getGraph()[i][j];
            }
        }
    }

    for (size_t t = 0; t < size; t++) {
        tempMat[size][t] = 0;
    }
    return BellmanFord(g, size, 0, distance, parent) == "There is a negative cycle.";
}

vector<vector<size_t>> DFS(const Graph& graph) {
    size_t size = graph.getGraph().size();
    vector<bool> visited(size, false);

    vector<vector<size_t>> dfsForest;  // Initialize a vector of vectors to store DFS forest

    for (int u = 0; u < size; u++) {
        if (!visited[(size_t)u]) {
            dfsForest.push_back(DFS_Visit(graph, (size_t)u, visited));  // Add the result of DFS visit to the forest
        }
    }
    return dfsForest;
}

vector<size_t> DFS_Visit(const Graph& graph, int vertex, vector<bool>& visited) {
    vector<size_t> dfsTree;

    size_t size = graph.getGraph().size();
    stack<size_t> s;  // This will be the list of the neighbor
    s.push((unsigned long) vertex);   // Add the vertex to the list
    visited[(unsigned long)vertex] = true;
    while (!s.empty()) {  // we will go through the list of his neighbors as long as it is not empty
        size_t u = s.top();
        s.pop();
        dfsTree.push_back(u);

        // loop over the neighbors
        for (size_t v = 0; v < size; v++) {
            if (graph.getGraph()[u][v] != 0 && !visited[v]) {
                s.push(v);
                visited[v] = true;  // We will mark it as a vertex that we passed over
            }
        }
    }
    return dfsTree;
}

void BFS(const Graph& graph, int start, vector<int>& distance, vector<int>& parent) {
    size_t size = graph.getGraph().size();
    queue<int> q;
    q.push(start);  // Push the starting vertex to the queue
    distance[(size_t)start] = 0;

    while (!q.empty()) {
        size_t u =(size_t) q.front();  // Get the front vertex from the queue
        q.pop();            // Remove the front vertex from the queue

        for (size_t v = 0; v < size; v++) {  // Iterate through the neighbors of vertex u
            if (graph.getGraph()[u][v] != 0) {
                if (distance[v] == BigNum) {
                    distance[v] = distance[u] + 1;  // Update the distance of vertex v
                    parent[v] = u;                  // Update the parent of vertex v
                    q.push(v);
                }
            }
        }
    }
}

string BellmanFord(const Graph& g, int start, int end, vector<int>& distance, vector<int>& parent) {
    size_t size = g.getGraph().size();
    for (size_t v = 0; v < size; v++) {
        distance[v] = BigNum; // Initialize distances to infinity
        parent[v] = -1;
    }
    distance[(size_t)start] = 0; // Set distance from start vertex to itself to 0
    for (size_t i = 0; i < size - 1; i++) {  // Passing n-1 time on every edge and for every edge we do relax
        for (size_t x = 0; x < size; x++) {
            for (size_t y = 0; y < size; y++) {
                if (g.getGraph()[x][y] == BigNum || distance[x] == BigNum) {
                    continue;
                }
                if (distance[x] + g.getGraph()[x][y] < distance[y]) {
                    distance[y] = distance[x] + g.getGraph()[x][y];
                    parent[y] = x;
                }
            }
        }
    }
     // Check for negative cycles
    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            if (g.getGraph()[x][y] == BigNum || distance[x] == BigNum) {
                continue;
            }
            if (distance[x] + g.getGraph()[x][y] < distance[y]) {
                return "There is a negative cycle.";
            }
        }
    }
    return "1"; // No negative cycle detected
}

bool dfsVisit(const Graph& g, size_t u, vector<Color>& colors, vector<int>& parent) {
    colors[u] = GRAY;
    for (size_t v = 0; v < g.numVertices(); ++v) {
        if (g.getGraph()[u][v] != 0) { // If there is an edge between u and v
            if (colors[v] == GRAY) {
                if (parent[u] != v && !g.getDirected()) {  // If not a directed graph and not a back edge
                    continue;
                }
                return true;  // Found a cycle
            } else if (colors[v] == WHITE) { // If the neighbor has not been visited
                parent[v] = u;
                if (dfsVisit(g, v, colors, parent)) {
                    return true;
                }
            }
        }
    }
    colors[u] = BLACK; // Mark vertex u as visited
    return false;
}

string Algorithms::isBipartite(const Graph& g) {
    // Bipartite graph check using BFS
    int numVertices = g.numVertices();
    vector<int> color((size_t)numVertices, -1);  // Initialize all vertices with no color (-1)
    queue<int> q;

    for (size_t i = 0; i < numVertices; ++i) {
        if (color[i] == -1) {
            color[i] = 0;  // Assign color 0 to the first vertex in the connected component
            q.push(i);
            while (!q.empty()) {
                size_t u = (size_t)q.front();
                q.pop();
                for (size_t v = 0; v < g.getGraph()[u].size(); ++v) {
                    if (g.getGraph()[u][v] != 0) {  // If there is an edge between u and v
                        if (color[v] == -1) {
                            color[v] = 1 - color[u];  // Assign opposite color to neighbor v
                            q.push(v);
                        } else if (color[v] == color[u]) {
                            return "0";  // Not bipartite
                        }
                    }
                }
            }
        }
    }
    // Print the partition of the bipartite graph
    vector<int> setA, setB;
    for (int i = 0; i < numVertices; ++i) {
        if (color[(size_t)i] == 0) {
            setA.push_back(i);
        } else {
            setB.push_back(i);
        }
    }
    cout << "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        cout << setA[i];
        if (i != setA.size() - 1) {
            cout << ", ";
        }
    }
    cout << "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        cout << setB[i];
        if (i != setB.size() - 1) {
            cout << ", ";
        }
    }

    cout << "}" << endl;
    return "1";  // Bipartite
}