#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Class representing an undirected graph
class Graph {
private:
  int vertices; // Number of vertices in the graph
  std::vector<std::vector<int>> adjacencyList; // Adjacency list to store edges
  std::unordered_map<std::string, int>
      vertexMap; // Map to store vertex labels and their indices
  std::vector<std::string>
      indexToLabel; // Vector to map indices back to vertex labels

public:
  // Constructor to initialize an empty graph
  Graph() : vertices(0) {}

  // Add a vertex to the graph with a given label
  void addVertex(const std::string &label) {
    // Check if the vertex already exists
    if (vertexMap.find(label) == vertexMap.end()) {
      vertexMap[label] = vertices; // Map the label to the current index
      indexToLabel.push_back(
          label); // Add the label to the index-to-label mapping
      adjacencyList.push_back(
          std::vector<int>()); // Add an empty adjacency list for the new vertex
      vertices++;              // Increment the vertex count
    }
  }

  // Add an edge between two vertices (undirected)
  void addEdge(const std::string &source, const std::string &destination) {
    // Add the source and destination vertices if they don't exist
    addVertex(source);
    addVertex(destination);

    int srcIdx = vertexMap[source]; // Get the index of the source vertex
    int destIdx =
        vertexMap[destination]; // Get the index of the destination vertex

    // Add the edge in both directions for an undirected graph
    adjacencyList[srcIdx].push_back(destIdx);
    adjacencyList[destIdx].push_back(srcIdx);
  }

  // Print the graph as an adjacency list
  void printGraph() {
    std::cout << "Graph representation (Adjacency List):" << std::endl;
    for (int i = 0; i < vertices; i++) {
      std::cout << indexToLabel[i] << " -> "; // Print the vertex label
      for (int neighbor : adjacencyList[i]) {
        std::cout << indexToLabel[neighbor]
                  << " "; // Print all adjacent vertices
      }
      std::cout << std::endl;
    }
  }

  // Perform Breadth-First Search (BFS) starting from a given vertex
  void BFS(const std::string &startVertex) {
    // Check if the start vertex exists
    if (vertexMap.find(startVertex) == vertexMap.end()) {
      std::cout << "Vertex not found!" << std::endl;
      return;
    }

    int startIdx = vertexMap[startVertex]; // Get the index of the start vertex
    std::unordered_set<int> visited; // Set to keep track of visited vertices
    std::queue<int> queue;           // Queue for BFS traversal

    // Start with the initial vertex
    visited.insert(startIdx); // Mark the start vertex as visited
    queue.push(startIdx);     // Enqueue the start vertex

    std::cout << "BFS traversal: ";

    while (!queue.empty()) {
      int current = queue.front(); // Get the front vertex in the queue
      queue.pop();                 // Remove it from the queue

      std::cout << indexToLabel[current] << " "; // Process the current vertex

      // Visit all adjacent vertices
      for (int neighbor : adjacencyList[current]) {
        if (visited.find(neighbor) == visited.end()) { // If not visited
          visited.insert(neighbor);                    // Mark as visited
          queue.push(neighbor);                        // Enqueue the neighbor
        }
      }
    }
    std::cout << std::endl;
  }

  // Perform Depth-First Search (DFS) starting from a given vertex
  void DFS(const std::string &startVertex) {
    // Check if the start vertex exists
    if (vertexMap.find(startVertex) == vertexMap.end()) {
      std::cout << "Vertex not found!" << std::endl;
      return;
    }

    int startIdx = vertexMap[startVertex]; // Get the index of the start vertex
    std::unordered_set<int> visited; // Set to keep track of visited vertices
    std::stack<int> stack;           // Stack for DFS traversal

    // Start with the initial vertex
    stack.push(startIdx); // Push the start vertex onto the stack

    std::cout << "DFS traversal: ";

    while (!stack.empty()) {
      int current = stack.top(); // Get the top vertex in the stack
      stack.pop();               // Remove it from the stack

      // If the vertex is not visited, mark it as visited and process it
      if (visited.find(current) == visited.end()) {
        visited.insert(current);                   // Mark as visited
        std::cout << indexToLabel[current] << " "; // Process the current vertex

        // Visit all adjacent vertices in reverse order
        // (to maintain similar order as recursive DFS)
        for (int i = adjacencyList[current].size() - 1; i >= 0; i--) {
          int neighbor = adjacencyList[current][i];
          if (visited.find(neighbor) == visited.end()) { // If not visited
            stack.push(neighbor); // Push the neighbor onto the stack
          }
        }
      }
    }
    std::cout << std::endl;
  }
};

int main() {
  // Create a graph
  Graph graph;

  // Add edges with string labels
  graph.addEdge("A", "B");
  graph.addEdge("A", "C");
  graph.addEdge("A", "D");
  graph.addEdge("B", "E");
  graph.addEdge("C", "D");

  // Print the graph
  graph.printGraph();

  // Apply BFS starting from vertex A
  graph.BFS("A");

  // Apply DFS starting from vertex A
  graph.DFS("A");

  return 0;
}
