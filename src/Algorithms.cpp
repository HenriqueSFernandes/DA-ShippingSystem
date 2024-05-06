//
// Created by memechanic on 04-05-2024.
//

#include "Algorithms.h"
#include "MutablePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <cmath>
#include <unordered_set>

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
        if(existingVertex != nullptr) {
            existingVertex->getInfo().setLongitude(stod(longitude));
            existingVertex->getInfo().setLongitude(stod(latitude));
        }

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
double Algorithms::tspBacktracking(vector<int> &path) {
    double ans = 1e9;
    path.resize(network.getNumVertex());
    vector<int> bestPath(network.getNumVertex());
    path[0] = 0;
    bestPath[0] = 0;
    network.findVertex(Node(0))->setVisited(true);
    findMinPathUpToN(0, network.getNumVertex(), 1, 0, ans, path, bestPath);
    path = bestPath;
    return ans;
}

void Algorithms::findMinPathUpToN(int curIndex, int n, int len, double cost, double &ans, vector<int> &path, vector<int> &bestPath) {
    auto ver = network.findVertex(Node(curIndex));
    if (len == n) {
        if(network.findVertex(Node(curIndex))->getAdj()[0]->getDest()->getInfo().getId() != 0) return;
        else{
            cost += network.findVertex(Node(curIndex))->getAdj()[0]->getWeight();
        }

        if (cost < ans) {
            ans = cost;
            bestPath = path; // Update bestPath if a better solution is found
        }
        return;
    }
    if (cost >= ans) return; // Prune unnecessary branches

    for (auto edge : ver->getAdj()) {
        auto neighbour = edge->getDest();
        if (!neighbour->isVisited()) {
            edge->getDest()->setVisited(true);
            path[len] = edge->getDest()->getInfo().getId();
            findMinPathUpToN(edge->getDest()->getInfo().getId(), n, len + 1, cost + edge->getWeight(), ans, path, bestPath);
            edge->getDest()->setVisited(false);
        }
    }
}

std::vector<Vertex<Node> *> Algorithms::prim(Graph<Node> * g) {
    // TODO
    //initializar valores de dist
    vector<Vertex<Node> *> MST;
    MutablePriorityQueue<Vertex<Node> > myq_queue;
    for( auto vertex : g->getVertexSet()) {
        vertex->setDist(INT_MAX);
        myq_queue.insert(vertex);
    }
    Vertex<Node> * head = g->getVertexSet().at(0);
    head->setDist(0); // first vertex in out mST
    myq_queue.decreaseKey(head);
    while(!myq_queue.empty()) {
        auto u=myq_queue.extractMin();
        u->setProcesssing(true);
        MST.push_back(u);
        for (auto edge : u->getAdj()) {
            Vertex<Node> *v = edge->getDest();
            if (!v->isProcessing() && edge->getWeight() < v->getDist()) {
                v->setDist(edge->getWeight());
                myq_queue.decreaseKey(v);
                v->setPath(edge);
            }
        }
    }


    return MST;
}
void dfs(Vertex<Node> *v, vector<int> &path) {
    path.push_back(v->getInfo().getId());
    v->setVisited(true);
    for (auto edge : v->getAdj()) {
        if ( !edge->getDest()->isVisited() && edge->getDest()->getPath()->getOrig()->getInfo()==v->getInfo()  ){
            dfs(edge->getDest(), path);
        }
    }
}
double Algorithms::tspTriangularAprox(vector<int> &path) {
    double ans = 0;
    vector<Vertex<Node> *> MST = prim(&network);
    auto ver= MST[0];
    dfs(ver, path);


    for (int i = 0; i < path.size() ; i++) {

        auto v = network.findVertex(path[i]);
        auto w = network.findVertex(path[i + 1]);
        if(i==path.size()-1) {
            w = network.findVertex(path[0]);
        }

        auto edges = v->getAdj();

        bool edgeExists = false;
        for (auto e : edges) {
            if (e->getDest()->getInfo().getId() == w->getInfo().getId()) {
                // Edge exists, use its distance
                ans += e->getWeight();
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists) {
            // Edge does not exist, calculate distance using haversine formula
            double dist = haversine(v->getInfo().getLatitude(), v->getInfo().getLongitude(), w->getInfo().getLatitude(), w->getInfo().getLongitude());
            ans += dist;
        }
    }


    return ans;


}

double Algorithms::haversine(double lat1, double lon1,
                                   double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}