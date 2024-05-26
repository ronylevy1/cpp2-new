#include "Graph.hpp"
using namespace ariel;

// helper function declaration
bool isContain(const Graph& other, const Graph& g);
//  end function declaration

void Graph::loadGraph(vector<vector<int>> temp_graph) {
    this->mat = temp_graph;
    int size = temp_graph.size();

    for (size_t i = 0; i < size; i++) {
        if (temp_graph[i].size() != size) {
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix");
        }
    }

    this->isWeigh = false;
    this->isDirected = false;
    for (size_t i = 0; i < size; i++) {  // Go all over the original graph and put there the values of the temp graph
        for (size_t j = 0; j < size; j++) {
            // If the graph is not weighted we will weighted it by 1
            if (mat[i][j] != 0 && mat[i][j] != 1) {
                this->isWeigh = true;  // If any edge has a weight other than 0 or 1, it's weighted
            }

            if (mat[i][j] != mat[j][i]) {
                this->isDirected = true;
            }
        }
    }
}

void Graph::printGraph() {
    int size = this->mat.size();
    bool sym = true;
    int num_of_edges = 0;
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            if (mat[i][j] != 0) {  // Its means that there ia an edge.
                num_of_edges++;
                if (mat[i][j] != mat[j][i]) {  // Not symetric
                    sym = false;
                }
            }
        }
    }

    if (sym) {
        num_of_edges = num_of_edges / 2;
    }

    std::cout << "Graph with " << size << " vertices and " << num_of_edges << " edges." << std::endl;
}

const vector<vector<int>>& Graph::getGraph() const {
    return this->mat;
}

vector<vector<int>>& Graph::getGraph() {
    return this->mat;
}

bool Graph::getWeighted() const {
    return this->isWeigh;
}

bool Graph::getDirected() const {
    return this->isDirected;
}

size_t Graph::numVertices() const {
    return mat.size();  // Assuming the size of mat represents the number of vertices
}

// part 2
Graph Graph::operator+(const Graph& other) const {
    if (other.getGraph().size() != this->getGraph().size() || other.getGraph()[0].size() != this->getGraph()[0].size()) {
        throw std::invalid_argument("The matrix need to be with the same size\n");
    }
    Graph tempGraph = *this;
    for (size_t i = 0; i < tempGraph.getGraph().size(); i++) {
        for (size_t j = 0; j < tempGraph.getGraph().size(); j++) {
            tempGraph.getGraph()[i][j] += other.getGraph()[i][j];
        }
    }
    return tempGraph;
}

Graph& Graph::operator+=(const Graph& other) {
    *this = other + *this;
    return *this;
}

Graph Graph::operator+() const {
    return *this;  // return copy of the graph
}

Graph& Graph::operator++() {
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            if (this->getGraph()[i][j] != 0) {
                this->getGraph()[i][j] = this->getGraph()[i][j] + 1;
            }
        }
    }
    return *this;
}

Graph Graph::operator++(int) {
    Graph newGraph = *this;
    ++*this;
    return newGraph;
}

Graph Graph::operator-(const Graph& other) const {
    if (other.getGraph().size() != this->getGraph().size()) {
        throw std::invalid_argument("The matrix need to be with the same size\n");
    }
    Graph tempGraph = *this;
    for (size_t i = 0; i < tempGraph.getGraph().size(); i++) {
        for (size_t j = 0; j < tempGraph.getGraph().size(); j++) {
            tempGraph.getGraph()[i][j] -= other.getGraph()[i][j];
        }
    }
    return tempGraph;
}

Graph& Graph::operator-=(const Graph& other) {
    if (other.getGraph().size() != this->getGraph().size()) {
        throw std::invalid_argument("The matrix needs to be of the same size\n");
    }

    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph()[i].size(); j++) {
            this->getGraph()[i][j] = this->getGraph()[i][j] - other.getGraph()[i][j];
        }
    }

    return *this;
}

Graph Graph::operator-() const {
    Graph newGraph = *this;
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            newGraph.getGraph()[i][j] = newGraph.getGraph()[i][j] * -1;
        }
    }
    return newGraph;
}

Graph& Graph::operator--() {
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            if (this->getGraph()[i][j] != 0) {
                this->getGraph()[i][j] = this->getGraph()[i][j] - 1;
            }
        }
    }
    return *this;
}

Graph Graph::operator--(int) {
    Graph newGraph = *this;
    --*this;
    return newGraph;
}

bool Graph::operator<(const Graph& other) const {
    // If the size of the matrix are equal, if their values are equal then it is considered that other is contained in this
    if (this->getGraph() == other.getGraph()) {
        return false;
    }

    if (isContain(*this, other)) {
        return true;
    }

    if (isContain(other, *this)) {
        return false;
    }

    if (this->numOfEdgs() < other.numOfEdgs()) {
        return true;
    }

    if (other.numOfEdgs() > this->numOfEdgs()) {
        return false;
    }

    bool ans = other.numVertices() > this->numVertices();
    return ans;
}

bool Graph::operator<=(const Graph& other) const {
    if ((*this < other) && (*this == other)) {  // If this is smaller then other and there equals
        return true;
    }
    return false;
}

bool Graph::operator>(const Graph& other) const {
    return other < *this;
}

bool Graph::operator>=(const Graph& other) const {
    return (*this > other) && (*this == other);  // If this is bigger then other and there equals
}

bool Graph::operator==(const Graph& other) const {
    bool ans = !(*this < other) && !(other < *this);
    return ans;
}

bool Graph::operator!=(const Graph& other) const {
    return !(other == *this);
}

Graph Graph::operator*(double num) const {
    Graph newGraph = *this;
    for (size_t i = 0; i < newGraph.getGraph().size(); i++) {
        for (size_t j = 0; j < newGraph.getGraph().size(); j++) {
            newGraph.getGraph()[i][j] = newGraph.getGraph()[i][j] * num;
        }
    }
    return newGraph;
}

Graph Graph::operator*(const Graph& other) const {
    // If there isnt if the same size
    if (this->getGraph().size() != other.getGraph().size() || this->getGraph()[0].size() != other.getGraph()[0].size()) {
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
    }
    // There is in the same size
    Graph newGraph = *this;
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            int sum = 0;
            for (size_t t = 0; t < this->getGraph().size(); t++) {
                sum = sum + this->getGraph()[i][t] * other.getGraph()[t][j];
            }
            newGraph.getGraph()[i][j] = sum;
        }
    }

    for (size_t k = 0; k < this->getGraph().size(); k++) {
        newGraph.getGraph()[k][k] = 0;
    }

    return newGraph;
}

Graph& Graph::operator*=(const Graph& other) {
    *this = (*this) * other;
    return *this;
}

Graph& Graph::operator*=(const double num) {
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            this->getGraph()[i][j] = num * this->getGraph()[i][j];
        }
    }
    return *this;
}

Graph& Graph::operator/=(const double num) {
    if (num == 0) {
        throw std::invalid_argument("You cant divide in 0\n");
    }
    for (size_t i = 0; i < this->getGraph().size(); i++) {
        for (size_t j = 0; j < this->getGraph().size(); j++) {
            this->mat[i][j] = (this->mat[i][j]) / num;
        }
    }
    return *this;
}

bool isContain(const Graph& other, const Graph& g) {
    if (g.getGraph().size() < other.getGraph().size()) {
        return false;
    }

    for (size_t i = 0; i <= g.getGraph().size() - other.getGraph().size(); i++) {
        for (size_t j = 0; j <= g.getGraph().size() - other.getGraph().size(); j++) {
            bool contain = true;  // Checks if the submatrix is ​​equal to other
            for (size_t k = 0; k < other.getGraph().size(); k++) {
                for (size_t m = 0; m < other.getGraph().size(); m++) {
                    if (g.getGraph()[i + k][j + m] != other.getGraph()[k][m]) {
                        contain = false;  // Marker then other isnt contine in this
                        break;
                    }
                }
                if (!contain) {  // If other isnt contained in this
                    break;
                }
            }
            if (contain) {  // If other contained in this
                return true;
            }
        }
    }
    return false;
}

int Graph::numOfEdgs() const {
    // int size = this->mat.size();
    bool sym = true;
    int num_of_edges = 0;
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat.size(); j++) {
            if (mat[i][j] != 0) {  // Its means that there ia an edge.
                num_of_edges++;
                if (mat[i][j] != mat[j][i]) {  // Not symetric
                    sym = false;
                }
            }
        }
    }

    if (sym) {
        num_of_edges = num_of_edges / 2;
    }

    return num_of_edges;
}