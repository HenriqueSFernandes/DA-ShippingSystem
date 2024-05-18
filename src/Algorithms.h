/// @file Algorithms.h
#ifndef SHIPPING_SYSTEM_ALGORITHMS_H
#define SHIPPING_SYSTEM_ALGORITHMS_H

#include <utility>
#include "Graph.h"
#include "Node.h"
#include <set>
#include <map>
#include <string>
#include <ostream>
#include <chrono>


using namespace std;

/**
 * @class Algorithms
 * @brief This class contains various algorithms used in the shipping system.
 *
 * The Algorithms class provides functions for reading nodes and edges from files,
 * solving the Travelling Salesperson Problem using different algorithms,
 * and calculating the haversine distance between two points.
 */
class Algorithms {
public:

    /**
     * @brief Constructs an instance of the Algorithms class.
     *
     * This constructor initializes the Algorithms class with the provided node and edge files.
     * The node and edge files are used to construct the network graph.
     *
     * @param node_file The name of the file containing the node data.
     * @param edge_file The name of the file containing the edge data.
     */
    Algorithms(string node_file, string edge_file) : nodeFile(std::move(node_file)), edgeFile(std::move(edge_file)) {}

    /**
     * @brief Reads nodes from a file and adds them to the network graph.
     *
     * This function reads node data from a file specified by the `nodeFile` member variable.
     * Each line in the file should represent a node and should be formatted as follows: id,longitude,latitude.
     * The function will ignore the first line of the file (header).
     *
     * If a node with the same id already exists in the network graph, the function will update the longitude and latitude of the existing node.
     * If the node does not exist, the function will create a new node and add it to the network graph.
     *
     * If the `nodeFile` member variable is empty, the function will print a message and return without doing anything.
     * If the file specified by `nodeFile` cannot be opened, the function will print an error message and return.
     *
     * After all nodes have been read and added to the network graph, the function will print a message and close the file.
     */
    void readNodes();

    /**
     * @brief Reads edges from a file and adds them to the network graph.
     *
     * This function reads edge data from a file specified by the `edgeFile` member variable.
     * Each line in the file should represent an edge and should be formatted as follows: originId,targetId,distance.
     * The function will ignore the first line of the file (header) unless the file is located in the "../data/Extra_Fully_Connected_Graphs/" directory.
     *
     * If an edge between the origin and target nodes already exists in the network graph, the function will update the distance of the existing edge.
     * If the edge does not exist, the function will create a new edge and add it to the network graph.
     *
     * If the `edgeFile` member variable is empty, the function will print a message and return without doing anything.
     * If the file specified by `edgeFile` cannot be opened, the function will print an error message and return.
     *
     * After all edges have been read and added to the network graph, the function will print a message and close the file.
     */
    void readEdges();

    /**
     * @brief Solves the Travelling Salesperson Problem using the Backtracking algorithm.
     *
     * This function attempts to find the shortest possible route that visits each node exactly once and returns to the origin node.
     * It uses the Backtracking algorithm, which builds a solution incrementally, one piece at a time, removing solutions that fail to satisfy the constraints of the problem at any point of time (by time, here, is referred to the time elapsed till reaching any level of the search tree).
     * Complexity: O(n!) TODO verify this
     *
     * @param path A reference to a vector of integers. The function will fill this vector with the order of nodes in the optimal path.
     * @return The total distance of the optimal path.
     */
    double tspBacktracking(vector<int> &path);

    /**
     * @brief Resets the network graph.
     *
     * This function iterates over all vertices in the network graph and sets their visited and processing status to false.
     * This is used to prepare the network graph for a new traversal or pathfinding operation.
     */
    void resetNetwork();

    /**
     * @brief Recursively finds the minimum path up to a given number of nodes.
     *
     * This function is a helper function for the tspBacktracking function.
     * It uses recursion and backtracking to find the shortest path that visits a specified number of nodes in the network graph.
     * Complexity is O(n!) TODO verify this
     *
     * @param curIndex The index of the current node.
     * @param n The total number of nodes to visit.
     * @param len The current length of the path.
     * @param cost The current cost of the path.
     * @param ans A reference to a double where the function will store the cost of the shortest path found.
     * @param path A reference to a vector of integers where the function will store the order of nodes in the current path.
     * @param bestPath A reference to a vector of integers where the function will store the order of nodes in the shortest path found.
     */
    void
    findMinPathUpToN(int curIndex, int n, int len, double cost, double &ans, vector<int> &path, vector<int> &bestPath);

    /**
     * @brief Implements the Prim's algorithm to find the Minimum Spanning Tree of a graph.
     *
     * This function uses a priority queue to select the next vertex to add to the MST. It starts with an arbitrary vertex,
     * sets its distance to 0, and then repeatedly adds the closest vertex that is not yet in the MST.
     * Complexity is O(E log V) TODO verify this
     *
     * @param g A pointer to the graph on which to run Prim's algorithm.
     * @return A vector of vertices that form the MST.
     */
    std::vector<Vertex<Node> *> prim(Graph<Node> *g);

    /**
     * @brief Implements the TSP using a triangular approximation.
     *
     * This function first generates a Minimum Spanning Tree (MST) using Prim's algorithm. Then, it performs a DFS on the MST to get a path.
     * For each node in the path, it checks if an edge exists in the original graph to the next node in the path. If it does, it adds the weight of the edge to the total cost.
     * If an edge does not exist, it calculates the distance between the two nodes using the haversine formula and adds this distance to the total cost.
     * Complexity is O(V^2) TODO verify this
     *
     * @param path A reference to a vector of integers where the function will store the order of nodes in the path.
     * @return The total cost of the path.
     */
    double tspTriangularApprox(vector<int> &path);

    /**
     * @brief Calculates the Haversine distance between two points on the Earth's surface.
     *
     * The Haversine formula calculates the shortest distance between two points on the surface of a sphere, given their longitudes and latitudes.
     * This function takes in the latitude and longitude of two points in degrees, converts them to radians, and then applies the Haversine formula to calculate the distance.
     * The result is returned in kilometers.
     *
     * @param lat1 Latitude of the first point in degrees.
     * @param lon1 Longitude of the first point in degrees.
     * @param lat2 Latitude of the second point in degrees.
     * @param lon2 Longitude of the second point in degrees.
     * @return The Haversine distance between the two points in kilometers.
     */
    double haversine(double lat1, double lon1,
                     double lat2, double lon2);

    /**
     * @brief Implements the Nearest Neighbour algorithm to solve the Travelling Salesman Problem (TSP).
     *
     * This function starts from a given node (in this case, the node with ID 0), and at each step, it selects the closest unvisited node as the next node to visit.
     * The distance between nodes is calculated using the weights of the edges in the graph. If an edge does not exist between the current node and the next node, the Haversine distance is used instead.
     * The function continues this process until all nodes have been visited, at which point it returns to the starting node.
     * The order of nodes visited is stored in the 'path' parameter, and the total cost of the path is returned as a double.
     * Complexity is O(V^2) TODO verify this
     *
     * @param path A reference to a vector of integers where the function will store the order of nodes in the path.
     * @return The total cost of the path.
     */
    double tspNearestNeighbour(vector<int> &path);

    /**
     * @brief Finds the closest node to the given node in the network.
     *
     * This function iterates over all the vertices in the network. For each vertex, it checks if an edge exists from the current node to the vertex and if the vertex has not been visited.
     * If these conditions are met, it calculates the Haversine distance between the current node and the vertex. If this distance is less than the minimum distance found so far, it updates the minimum distance and sets the closest vertex to the current vertex.
     * After iterating over all the vertices, it returns the closest vertex.
     * Complexity is O(V^2) TODO verify this
     *
     * @param current A pointer to the current vertex.
     * @return A pointer to the closest vertex to the current vertex.
     */
    Vertex<Node> *findClosestNode(Vertex<Node> *current);

    /**
     * @brief Checks if a solution to the Travelling Salesman Problem (TSP) is feasible from a given starting node.
     *
     * This function uses a breadth-first search (BFS) algorithm to traverse the graph from the given starting node.
     * It maintains a queue of nodes to visit and a set of visited nodes. It starts by adding the starting node to the queue and the visited set.
     * Then, it enters a loop where it dequeues a node, and for each of its adjacent nodes, if the node has not been visited, it adds it to the queue and the visited set.
     * The function continues this process until the queue is empty, which means all reachable nodes from the starting node have been visited.
     * Finally, it checks if the number of visited nodes is equal to the total number of nodes in the graph. If they are equal, it means all nodes are reachable from the starting node, so a solution to the TSP is feasible, and the function returns true. Otherwise, it returns false.
     * Complexity is O(V + E) TODO verify this
     *
     * @param start The ID of the starting node.
     * @return True if a solution to the TSP is feasible from the starting node, false otherwise.
     */
    bool isTSPFeasible(int start);

    /**
     * @brief Solves the TSP using a modified nearest neighbour approach.
     *
     * This function first checks if a solution to the TSP is feasible from the given starting node by calling the isTSPFeasible function.
     * If a solution is not feasible, it returns infinity.
     *
     * Then, it initializes the current vertex to the starting node and marks it as visited.
     * It also initializes a set to keep track of nodes that have been backtracked.
     *
     * The function then enters a loop where it iterates over all the vertices in the graph.
     * For each vertex, it checks if it is the last vertex to be visited. If it is, it adds the edge weight from the current vertex to the starting node to the total cost and adds the starting node to the path.
     * If the current vertex is not the last vertex to be visited, it finds the unvisited vertex with the smallest edge weight from the current vertex and sets it as the next vertex.
     * If no such vertex exists, it backtracks to the previous vertex in the path and continues the process.
     *
     * The function continues this process until all vertices have been visited. It then returns the total cost of the path.
     * Complexity is O(V^2) TODO verify this
     *
     * @param path A reference to a vector that will be filled with the order of nodes visited in the optimal path.
     * @param backs A reference to an integer that will be filled with the number of backtracks made during the search.
     * @param start The ID of the starting node.
     * @return The total cost of the optimal path.
     */
    double tspModifiedNearestNeighbour(std::vector<int>& path, int& backs, int start);

    /**
     * @brief Gets the name of the node file.
     * @return The name of the node file.
     */
    string getNodeFile();

    /**
     * @brief Gets the name of the edge file.
     * @return The name of the edge file.
     */
    string getEdgeFile();

private:
    Graph<Node> network;
    string nodeFile;
    string edgeFile;
};


#endif //SHIPPING_SYSTEM_ALGORITHMS_H
