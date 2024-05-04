//
// Created by memechanic on 04-05-2024.
//

#include "Algorithms.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

void Algorithms::readNodes() {
    cout << "Loading nodes..." << endl;
    string id, longitude, latitude;
    ifstream nodeCsv(nodeFile);

    if (!nodeCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    getline(nodeCsv, line); // Ignore header

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(nodeCsv, line)) {
        istringstream iss(line);
        getline(iss, id, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, '\r');
        Node node(stoi(id));
        node.setLongitude(stod(longitude));
        node.setLongitude(stod(latitude));
        network.addVertex(node);
        //cout << "Read node with id: " << id << ", longitude: " << longitude << ", latitude: " << latitude << "\n";
    }

    cout << "Finished loading nodes!" << "\n";

    nodeCsv.close();
}

void Algorithms::readEdges() {
    cout << "Loading edges..." << endl;
    string originId;
    string targetId;
    string distance;
    ifstream edgeCsv(edgeFile);

    if (!edgeCsv) {
        cerr << "Failed to open file\n";
        return;
    }

    string line;
    if (edgeFile.find("../data/Extra_Fully_Connected_Graphs/") != 0) {
        getline(edgeCsv, line); // Ignore header
    }

    // Iterate over every line of the file, split the line, create a new class and append that class to the list of classes.
    while (getline(edgeCsv, line)) {
        istringstream iss(line);
        getline(iss, originId, ',');
        getline(iss, targetId, ',');
        getline(iss, distance, '\r');
        int s = stoi(originId);
        int d = stoi(targetId);
        double dis = stod(distance);
        auto source = network.findVertex(Node(s));
        auto dest = network.findVertex(Node(d));
        network.addEdge(source->getInfo(), dest->getInfo(), dis);
        //cout << "Read edge from node " << originId << " to node " << targetId << ", distance: " << distance << "\n";
    }

    cout << "Finished loading edges!" << "\n";

    edgeCsv.close();
}