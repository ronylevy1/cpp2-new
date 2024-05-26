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
vector<size_t> DFS_Visit(const Graph& graph, int vertex, vector<bool>& visited);
void BFS(const Graph& graph, int start,  vector<int>& distance, vector<int>& parent);
string BellmanFord(const Graph& graph, int start, int end, vector<int>& distance, vector<int>& parent);
bool dfsVisit(const Graph& graph, size_t node, vector<Color>& colors, vector<int>& parent);
//  end function declaration

bool ariel::Algorithms::isConnected(const Graph& graph) {
    if (graph.getGraph().empty()) {
        return true;
    }

    vector<vector<size_t>> firstDfs = DFS(graph);

    if (firstDfs.size() == 1) {  // Means that there is one tree - the graph is directed
        return true;
    }

    // Do second DFS (visit) from the root on the lsat tree
    size_t lastTreeRoot = firstDfs.back().front();

    vector<bool> visited(graph.getGraph().size(), false);                // we dont visit in any vertex yet
    vector<size_t> secondDfs = DFS_Visit(graph, lastTreeRoot, visited);  // dfs-visit from the root
    return secondDfs.size() == graph.getGraph().size();                  // check if dfs-visit discover all the graph
}

std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
    // If the graph is not weighted, use BFS to find the shortest path
    vector<int> distance(graph.numVertices(), BigNum);
    vector<int> parent(graph.numVertices(), -1);  // This is will be the path that we will print to see the shortest path

    if (!graph.getWeighted()) {
        BFS(graph, start, distance, parent);
    } else {
        // Use Bellman-Ford
        string ans = BellmanFord(graph, start, end, distance, parent);
        if (ans != "1") {  // There is no negative cycle
            return ans;
        }
    }

    if (distance[(size_t)end] == BigNum ) {  // Check if there is a path
        return "-1";
    }

    string path = std::to_string(end);
    int tempNode = parent[(size_t)end];
    while(tempNode!=-1){
        path = std::to_string(tempNode) +"->" + path;
        tempNode = parent[(size_t)tempNode];
    }
    return path;
}

bool Algorithms::isContainsCycle(const Graph& graph) {
    vector<int> parent(graph.numVertices(), -1); // Initialize parent vector with -1
    vector<Color> colors(graph.numVertices(), WHITE); // Initialize colors vector with WHITE
    for (size_t i = 0; i < graph.numVertices(); ++i) {
        if (colors[i] == WHITE && dfsVisit(graph, i, colors, parent)) {
            return true;
        }
    }
    return false; // No cycle found in the graph
}

bool Algorithms::negativeCycle(const Graph& graph) {
    vector<int> distance(graph.numVertices(), -1);
    vector<int> parent(graph.numVertices(), -1);  // This is will be the path that we will print to see the shortest path

    size_t size = graph.getGraph().size();
    vector<vector<int>> tempMat(size + 1, vector<int>(size + 1, BigNum));  // New mat. on here we will do bellman ford
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (graph.getGraph()[i][j] == 0) {
                tempMat[i][j] = graph.getGraph()[i][j];
            }
        }
    }

    for (size_t temp = 0; temp < size; temp++) {
        tempMat[size][temp] = 0;
    }
    return BellmanFord(graph, size, 0, distance, parent) == "There is a negative cycle.";
}

vector<vector<size_t>> DFS(const Graph& graph) {
    size_t size = graph.getGraph().size();
    vector<bool> visited(size, false);

    vector<vector<size_t>> dfsForest;  // Initialize a vector of vectors to store DFS forest

    for (int node = 0; node < size; node++) {
        if (!visited[(size_t)node]) {
            dfsForest.push_back(DFS_Visit(graph, (size_t)node, visited));  // Add the result of DFS visit to the forest
        }
    }
    return dfsForest;
}

vector<size_t> DFS_Visit(const Graph& graph, int vertex, vector<bool>& visited) {
    vector<size_t> dfsTree;

    size_t size = graph.getGraph().size();
    stack<size_t> neighborlist;  // This will be the list of the neighbor
    neighborlist.push((unsigned long) vertex);   // Add the vertex to the list
    visited[(unsigned long)vertex] = true;
    while (!neighborlist.empty()) {  // we will go through the list of his neighbors as long as it is not empty
        size_t firstNode = neighborlist.top();
        neighborlist.pop();
        dfsTree.push_back(firstNode);

        // loop over the neighbors
        for (size_t index = 0; index < size; index++) {
            if (graph.getGraph()[firstNode][index] != 0 && !visited[index]) {
                neighborlist.push(index);
                visited[index] = true;  // We will mark it as a vertex that we passed over
            }
        }
    }
    return dfsTree;
}

void BFS(const Graph& graph, int start, vector<int>& distance, vector<int>& parent) {
    size_t size = graph.getGraph().size();
    queue<int> queue;
    queue.push(start);  // Push the starting vertex to the queue
    distance[(size_t)start] = 0;

    while (!queue.empty()) {
        size_t frontVertex =(size_t) queue.front();  // Get the front vertex from the queue
        queue.pop();            // Remove the front vertex from the queue

        for (size_t node = 0; node < size; node++) {  // Iterate through the neighbors of vertex u
            if (graph.getGraph()[frontVertex][node] != 0) {
                if (distance[node] == BigNum) {
                    distance[node] = distance[frontVertex] + 1;  // Update the distance of vertex v
                    parent[node] = frontVertex;                  // Update the parent of vertex v
                    queue.push(node);
                }
            }
        }
    }
}

string BellmanFord(const Graph& graph, int start, int end, vector<int>& distance, vector<int>& parent) {
    size_t size = graph.getGraph().size();
    for (size_t node = 0; node < size; node++) {
        distance[node] = BigNum; // Initialize distances to infinity
        parent[node] = -1;
    }
    distance[(size_t)start] = 0; // Set distance from start vertex to itself to 0
    for (size_t i = 0; i < size - 1; i++) {  // Passing n-1 time on every edge and for every edge we do relax
        for (size_t x = 0; x < size; x++) {
            for (size_t index3 = 0; index3 < size; index3++) {
                if (graph.getGraph()[x][index3] == BigNum || distance[x] == BigNum) {
                    continue;
                }
                if (distance[x] + graph.getGraph()[x][index3] < distance[index3]) {
                    distance[index3] = distance[x] + graph.getGraph()[x][index3];
                    parent[index3] = x;
                }
            }
        }
    }
     // Check for negative cycles
    for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size; y++) {
            if (graph.getGraph()[x][y] == BigNum || distance[x] == BigNum) {
                continue;
            }
            if (distance[x] + graph.getGraph()[x][y] < distance[y]) {
                return "There is a negative cycle.";
            }
        }
    }
    return "1"; // No negative cycle detected
}

bool dfsVisit(const Graph& graph, size_t node, vector<Color>& colors, vector<int>& parent) {
    colors[node] = GRAY;
    for (size_t v = 0; v < graph.numVertices(); ++v) {
        if (graph.getGraph()[node][v] != 0) { // If there is an edge between u and v
            if (colors[v] == GRAY) {
                if (parent[node] != v && !graph.getDirected()) {  // If not a directed graph and not a back edge
                    continue;
                }
                return true;  // Found a cycle
            } else if (colors[v] == WHITE) { // If the neighbor has not been visited
                parent[v] = node;
                if (dfsVisit(graph, v, colors, parent)) {
                    return true;
                }
            }
        }
    }
    colors[node] = BLACK; // Mark vertex u as visited
    return false;
}

string Algorithms::isBipartite(const Graph& graph) {
    // Bipartite graph check using BFS
    int numVertices = graph.numVertices();
    vector<int> color((size_t)numVertices, -1);  // Initialize all vertices with no color (-1)
    queue<int> queue;

    for (size_t i = 0; i < numVertices; ++i) {
        if (color[i] == -1) {
            color[i] = 0;  // Assign color 0 to the first vertex in the connected component
            queue.push(i);
            while (!queue.empty()) {
                size_t front = (size_t)queue.front();
                queue.pop();
                for (size_t node = 0; node < graph.getGraph()[front].size(); ++node) {
                    if (graph.getGraph()[front][node] != 0) {  // If there is an edge between u and v
                        if (color[node] == -1) {
                            color[node] = 1 - color[front];  // Assign opposite color to neighbor v
                            queue.push(node);
                        } else if (color[node] == color[front]) {
                            return "0";  // Not bipartite
                        }
                    }
                }
            }
        }
    }
    // Print the partition of the bipartite graph
    vector<int> setA;
    vector<int> setB;
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