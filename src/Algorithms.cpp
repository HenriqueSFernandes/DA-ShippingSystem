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
        auto existingVertex = network.findVertex(Node(stoi(id)));
        existingVertex->getInfo().setLongitude(stod(longitude));
        existingVertex->getInfo().setLongitude(stod(latitude));
        cout << "Node with id: " << id << " was given longitude: " << longitude << " & latitude: " << latitude << "\n";
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

        auto origin = Node(s);
        auto source = network.findVertex(origin);
        if (source == nullptr) {
            network.addVertex(origin);
            source = network.findVertex(origin);
            cout << "Created node with id: " << originId << "\n";
        }

        auto target = Node(d);
        auto dest = network.findVertex(target);
        if (dest == nullptr) {
            network.addVertex(target);
            dest = network.findVertex(target);
            cout << "Created node with id: " << targetId << "\n";
        }

        double dis = stod(distance);
        network.addBidirectionalEdge(source->getInfo(), dest->getInfo(), dis);
        cout << "Read edge from node " << originId << " to node " << targetId << ", distance: " << distance << "\n";
    }

    cout << "Finished loading edges!" << "\n";

    edgeCsv.close();
}