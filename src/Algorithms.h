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
 * @brief The main class of the program. It is responsible for running all the algorithms and controlling the network.
 */
class Algorithms {
public:
    /**
     * @brief Constructor that takes the name of the files as arguments.
     * @param node_file The name of the file with the nodes.
     * @param edge_file The name of the file with the edges.
     */
    Algorithms(string node_file, string edge_file) : nodeFile(std::move(node_file)), edgeFile(std::move(edge_file)) {}

    /**
     * @brief Reads the contents of the nodes file.
     */
    void readNodes();

    /**
     * @brief Reads the contents of the edges file.
     */
    void readEdges();

    /**
     * @brief Backtracking solution to the Travelling Salesperson Problem.
     * @param path TODO
     * Complexity: TODO
     * More information: TODO
     * @return TODO
     */
    double tspBacktracking(vector<int> &path);

    void resetNetwork();

    /**
     * @brief TODO
     * @param curIndex TODO
     * @param n TODO
     * @param len TODO
     * @param cost TODO
     * @param ans TODO
     * @param path TODO
     * @param bestPath TODO
     * Complexity: TODO
     * More information: TODO
     */
    void
    findMinPathUpToN(int curIndex, int n, int len, double cost, double &ans, vector<int> &path, vector<int> &bestPath);

    /**
     * @brief TODO
     * @param g TODO
     * Complexity: TODO
     * More information: TODO
     * @return TODO
     */
    std::vector<Vertex<Node> *> prim(Graph<Node> *g);

    /**
     * @brief TODO
     * @param path TODO
     * Complexity: TODO
     * More infomation: TODO
     * @return TODO
     */
    double tspTriangularApprox(vector<int> &path);

    /**
     * @brief This function uses the haversine distance to calculate distance between 2 points on a sphere.
     * @param lat1 First point latitude.
     * @param lon1 First point longitude.
     * @param lat2 Second point latitude.
     * @param lon2 Second point longitude.
     * @return The distance between the points.
     */
    double haversine(double lat1, double lon1,
                     double lat2, double lon2);


    double tspNearestNeighbour(vector<int> &path);

    Vertex<Node> *findClosestNode(Vertex<Node> *current);

    bool isTSPFeasible(int start);

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
    Graph<Node> network;
    double dijkstra(Vertex<Node> *source, Vertex<Node> *dest, vector<int> &path);

    void MakeGraphComeplete();

private:

    string nodeFile;
    string edgeFile;
};


#endif //SHIPPING_SYSTEM_ALGORITHMS_H
