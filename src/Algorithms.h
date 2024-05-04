//
// Created by memechanic on 04-05-2024.
//

#ifndef SHIPPING_SYSTEM_ALGORITHMS_H
#define SHIPPING_SYSTEM_ALGORITHMS_H

#include <utility>
#include "Graph.h"
#include "Node.h"
#include <set>
#include <map>
#include <string>
#include <ostream>


using namespace std;

class Algorithms {
public:
    Algorithms(string node_file, string edge_file) : nodeFile(node_file), edgeFile(edge_file) {}

    void readNodes();

    void readEdges();

    double tspBacktracking(vector<int>  &path);

    void findMinPathUpToN(int curIndex,  int n, int len, double cost, double & ans, vector<int> & path,vector<int> & bestPath);

private:
    Graph<Node> network;
    string nodeFile;
    string edgeFile;
};


#endif //SHIPPING_SYSTEM_ALGORITHMS_H
