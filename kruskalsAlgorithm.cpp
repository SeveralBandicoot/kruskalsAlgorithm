/*

Research - Kruskal's Algorithm

12/4/2024

@AJ Enrique Arguello

Objectives: Research a new topic related to Data Structures & Algorithms. Or choose a previous topic and research commands/functions that support the Data Structure chosen (that hasn't been discussed previously in class). 

Create a program to demonstrate your Research Topic. 

=====================================================================

* Kruskals Algorithm: A "greedy" algorithm that finds trhe MST by sorting the edges in non-decreasing order of their weight & adding then to the MST. If a cycle if found, it is disregarded.

* Minimum Spanning Tree (MST): The MST of a graph is a subset of the edges that connect all vertices w/o any cycles & with minimum possible total edge weight

Step 1: Sort all edges in a non-decreasing order by their weight 

Step 2: Initalize MST as an empty set

Step 3: Create a data structure with all vertices, where each vertex is its own set 

Step 4: Applied to each edge in data set: 
  a.) If an edge connects to two different sets, add it to the MST
  b.) Merge the two sets 

Step 5: Repeat until the MST conrtains v-1 edges 

Step 6: Return the MST & its total weight

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// class to represent edges in the graph
class Edge {
  public:
    int src, dest, weight; // source, destination, and weight of edge
};
// class to represent a graph 
class Graph {
  public:
    int vertice, edge; // # of vertices and edges in the graph
    vector<Edge> edges; // list to store all edges 

    Graph(int vertice, int edge) { // intitializes graph with a given # of vertices and edges (constructor)
      this->vertice = vertice;
      this->edge = edge;
    }

    void addEdge(int u, int v, int w) { // addes an edge to the graph 
      edges.push_back({u, v, w}); // add an edge with u "source", v "destination", and weight ("weight")
    }
};
// class to represent subsets for union-find
class Subset { 
  public:
    int parent, rank; // "parent" points to parent within subset, "rank" helps optimize union operations
};

// find parent of a subset with path compression
int find(Subset subsets[], int i) {
  if (subsets[i].parent != i)
    subsets[i].parent = find(subsets, subsets[i].parent);
  return subsets[i].parent;
}

// union of two subsets by rank-based optimization
void Union(Subset subsets[], int x, int y) {
  int xroot = find(subsets, x); // find root within subset containing 'x'
  int yroot = find(subsets, y); // find root within subset containing 'y'
  // attach smaller rank tree under larger rank tree 
  if (subsets[xroot].rank < subsets[yroot].rank)
    subsets[xroot].parent = yroot;
  else if (subsets[xroot].rank > subsets[yroot].rank)
    subsets[yroot].parent = xroot;
  else {
    subsets[yroot].parent = xroot; // if ranks are equal, make one root and increment its rank
    subsets[xroot].rank++;
  }
}

//  function for sorting edges by weight
bool compare(Edge e1, Edge e2) {
  return e1.weight < e2.weight; // returns true if weight of "e1" is less than the weight of "e2"
}

// kruskal's MST algorithm
void kruskalsMST(Graph& graph) {
  vector<Edge> result; // vector to store edges into the MST
  int v = graph.vertice; // number of vertices within the graph

  // Step 1: Sort all edges in increasing order of weight
  sort(graph.edges.begin(), graph.edges.end(), compare);
  // allocate memory for the subsets
  Subset* subsets = new Subset[v];
  for (int i = 0; i < v; ++i) {
    subsets[i].parent = i; // each vertex is its own parent initially 
    subsets[i].rank = 0; // rank is initialized to 0 
  }

  int e = 0; // # of edges in MST
  int i = 0; // index to iterate through sorted edges

  while (e < v - 1 && i < graph.edges.size()) { // iterate until the MST contains 'v-1' edges
    // Step 2: Pick the smallest edge. Check if it forms a cycle
    Edge next_edge = graph.edges[i++];
    int x = find(subsets, next_edge.src); // find the parent of source vector
    int y = find(subsets, next_edge.dest); // find the parent of destination vector

    // if adding this edge doesn't cause a cycle
    if (x != y) {
      result.push_back(next_edge); // add the edge to the result 
      Union(subsets, x, y); // run union of the two subsets
      e++; // edge counter is incremented for MST
    }
  }
  // Step 3: Print the edges in MST
  cout << "Edge \tWeight\n";
  for (int i = 0; i < result.size(); ++i)
    cout << result[i].src << "-" << result[i].dest << "\t" << result[i].weight << endl;

  delete[] subsets; // free memory
}

int main() {
  int V = 5, E = 7; // number of vertices and edges 
  Graph graph(V, E); // create a graph with 'V' vertices and 'E' edges
  // add edges to graph
  graph.addEdge(0, 1, 2);
  graph.addEdge(0, 2, 3);
  graph.addEdge(1, 3, 15);
  graph.addEdge(1, 4, 2);
  graph.addEdge(2, 4, 1);
  graph.addEdge(2, 3, 7);
  graph.addEdge(3, 4, 2);
  // find/print MST using algorithm
  kruskalsMST(graph);

  return 0;
}
