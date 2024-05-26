#pragma once
#include <iostream>
#include <vector>

using std::vector;

namespace ariel {
class Graph {
   private:
    bool isDirected = false;  // Is not directed
    bool isWeigh = false;     // Is not weighted
    vector<vector<int>> mat;

   public:
    const vector<vector<int>>& getGraph() const;
    vector<vector<int>>& getGraph();
    void loadGraph(vector<vector<int>>);
    void printGraph();
    bool getWeighted() const;
    bool getDirected() const;
    size_t numVertices() const;

    // part 2
    int numOfEdgs() const;
    Graph operator+(const Graph& other) const;
    Graph& operator+=(const Graph& other);  // Return the reference to the real object
    Graph operator+() const;

    Graph& operator++();    // ++Graph
    Graph operator++(int);  // Graph++

    Graph operator-(const Graph& other) const;
    Graph& operator-=(const Graph& other);  // Return the reference to the real object
    Graph operator-() const;

    Graph& operator--();    // --Graph
    Graph operator--(int);  // Graph--

    bool operator<(const Graph& other) const;
    bool operator<=(const Graph& other) const;

    bool operator>(const Graph& other) const;  // G2 is mat and G1 is other, so it will return true if other is contained in mat
    bool operator>=(const Graph& other) const;

    bool operator==(const Graph& other) const;
    bool operator!=(const Graph& other) const;

    Graph operator*(double num) const;
    Graph operator*(const Graph& other) const;
    Graph& operator*=(const Graph& other);
    Graph& operator*=(const double num);

    Graph& operator/=(const double num);

    friend std::ostream& operator<<(std::ostream& st, const Graph& other) {
        for (size_t i = 0; i < other.getGraph().size(); i++) {
            st << "[";
            for (size_t j = 0; j < other.getGraph().size(); j++) {
                st << other.getGraph()[i][j];           // Add the current element to thr output
                if (j < other.getGraph().size() - 1) {  // If it is not the last element, add: ,
                    st << ", ";
                }
            }
            st << "]";
            if (i < other.getGraph().size() - 1) {  // If it is not the ladt line, add: ,
                st << ", ";
            }
        }
        st << "\n";
        return st;
    }
};
};  // namespace ariel