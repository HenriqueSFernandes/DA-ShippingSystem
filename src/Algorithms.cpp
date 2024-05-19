#include "Algorithms.h"
#include "MutablePriorityQueue.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <climits>
#include <cmath>
#include <unordered_set>
#include <cfloat>

void Algorithms::readNodes() {
    if (nodeFile.empty()){
        cout << "The node file is not needed\n";
        return;
    }
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
        if (existingVertex != nullptr) {
            Node new_node = Node(existingVertex->getInfo().getId());
            new_node.setLongitude(stod(longitude));
            new_node.setLatitude(stod(latitude));
            existingVertex->setInfo(new_node);
        }
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
        }

        auto target = Node(d);
        auto dest = network.findVertex(target);
        if (dest == nullptr) {
            network.addVertex(target);
            dest = network.findVertex(target);
        }

        double dis = stod(distance);
        network.addBidirectionalEdge(source->getInfo(), dest->getInfo(), dis);    }

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

void Algorithms::findMinPathUpToN(int curIndex, int n, int len, double cost, double &ans, vector<int> &path,
                                  vector<int> &bestPath) {
    auto ver = network.findVertex(Node(curIndex));
    if (len == n) {
        if (network.findVertex(Node(curIndex))->getAdj()[0]->getDest()->getInfo().getId() != 0) return;
        else {
            cost += network.findVertex(Node(curIndex))->getAdj()[0]->getWeight();
        }

        if (cost < ans) {
            ans = cost;
            bestPath = path; // Update bestPath if a better solution is found
        }
        return;
    }
    if (cost >= ans) return; // Prune unnecessary branches

    for (auto edge: ver->getAdj()) {
        auto neighbour = edge->getDest();
        if (!neighbour->isVisited()) {
            edge->getDest()->setVisited(true);
            path[len] = edge->getDest()->getInfo().getId();
            findMinPathUpToN(edge->getDest()->getInfo().getId(), n, len + 1, cost + edge->getWeight(), ans, path,
                             bestPath);
            edge->getDest()->setVisited(false);
        }
    }
}

std::vector<Vertex<Node> *> Algorithms::prim(Graph<Node> *g) {
    //initializar valores de dist
    vector<Vertex<Node> *> MST;
    MutablePriorityQueue<Vertex<Node> > myq_queue;
    for (auto vertex: g->getVertexSet()) {
        vertex.second->setDist(INT_MAX);
        myq_queue.insert(vertex.second);
    }
    Vertex<Node> *head = g->getVertexSet().at(0);
    head->setDist(0); // first vertex in out mST
    myq_queue.decreaseKey(head);
    while (!myq_queue.empty()) {
        auto u = myq_queue.extractMin();
        u->setProcesssing(true);
        MST.push_back(u);
        for (auto edge: u->getAdj()) {
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
    for (auto edge: v->getAdj()) {
        if (!edge->getDest()->isVisited() && edge->getDest()->getPath()->getOrig()->getInfo() == v->getInfo()) {
            dfs(edge->getDest(), path);
        }
    }
}

double Algorithms::tspTriangularApprox(vector<int> &path) {
    double ans = 0;
    vector<Vertex<Node> *> MST = prim(&network);
    auto ver = MST[0];
    dfs(ver, path);


    for (int i = 0; i < path.size(); i++) {

        auto v = network.findVertex(Node(path[i]));
        auto w = network.findVertex(Node(path[i + 1]));
        if (i == path.size() - 1) {
            w = network.findVertex(Node(path[0]));
        }

        auto edges = v->getAdj();

        bool edgeExists = false;
        for (auto e: edges) {
            if (e->getDest()->getInfo().getId() == w->getInfo().getId()) {
                // Edge exists, use its distance
                ans += e->getWeight();
                edgeExists = true;
                break;
            }
        }

        if (!edgeExists) {
            // Edge does not exist, calculate distance using haversine formula
            double dist = haversine(v->getInfo().getLatitude(), v->getInfo().getLongitude(), w->getInfo().getLatitude(),
                                    w->getInfo().getLongitude());
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

double Algorithms::tspNearestNeighbour(vector<int> &path) {
    for (auto vertex: network.getVertexSet()) {
        vertex.second->setVisited(false);
    }

    Vertex<Node> *currVertex = network.findVertex(Node(0));
    path.push_back(0);
    Vertex<Node> *nextVertex;
    currVertex->setVisited(true);
    double ans = 0;
    int curr_visit = 1;

    while (curr_visit < network.getNumVertex()) {
        double minDistance = numeric_limits<double>::max();
        for (auto edge: currVertex->getAdj()) {
            if (edge->getWeight() < minDistance && !edge->getDest()->isVisited()) {
                minDistance = edge->getWeight();
                nextVertex = edge->getDest();
            }
        }

        if (currVertex == nextVertex) {
            nextVertex = findClosestNode(currVertex);
            minDistance = haversine(currVertex->getInfo().getLatitude(), currVertex->getInfo().getLongitude(),
                                    nextVertex->getInfo().getLatitude(), nextVertex->getInfo().getLongitude());
        }

        ans += minDistance;
        path.push_back(nextVertex->getInfo().getId());
        curr_visit++;
        nextVertex->setVisited(true);
        currVertex = nextVertex;
    }

    auto first = network.findVertex(Node(0))->getInfo();
    ans += currVertex->getAdj()[0] == nullptr ? haversine(currVertex->getInfo().getLatitude(), currVertex->getInfo().getLongitude(),
                                                          first.getLatitude(), first.getLongitude()) :
           currVertex->getAdj()[0]->getWeight();
    path.push_back(0);

    return ans;
}

Vertex<Node> *Algorithms::findClosestNode(Vertex<Node> *current) {
    auto minDistance = numeric_limits<double>::max();
    Vertex<Node> *closest;
    for (auto vertex: network.getVertexSet()) {
        for (auto edge: current->getAdj()) {
            if (edge->getDest() == vertex.second || vertex.second->isVisited())
                continue;
        }
        double distance = haversine(current->getInfo().getLatitude(), current->getInfo().getLongitude(),
                                    vertex.second->getInfo().getLatitude(), vertex.second->getInfo().getLongitude());
        if (distance < minDistance) {
            minDistance = distance;
            closest = vertex.second;
        }
    }

    return closest;
}

bool Algorithms::isTSPFeasible(int start) {
    std::queue<Vertex<Node>*> q;
    std::set<Vertex<Node>*> visited;

    Vertex<Node>* startVertex = network.findVertex(Node(start));
    if (!startVertex) return false;

    q.push(startVertex);
    visited.insert(startVertex);

    while (!q.empty()) {
        Vertex<Node>* curr = q.front();
        q.pop();

        for (auto edge : curr->getAdj()) {
            Vertex<Node>* dest = edge->getDest();
            if (visited.find(dest) == visited.end()) {
                visited.insert(dest);
                q.push(dest);
            }
        }
    }

    return visited.size() == network.getNumVertex();
}

double Algorithms::tspModifiedNearestNeighbour(std::vector<int>& path, int& backs, int start) {
    if (!isTSPFeasible(start)) {
        return std::numeric_limits<double>::infinity(); // Indicate that TSP is not possible
    }

    for (auto vertex : network.getVertexSet()) {
        vertex.second->setVisited(false);
    }

    Vertex<Node>* currVertex = network.findVertex(Node(start));
    path.push_back(start);
    currVertex->setVisited(true);
    double ans = 0;
    int curr_visit = 1;
    int backtracks = 0;
    bool finished = false;
    std::unordered_set<int> backtrackedNodes; // set de vértices sem saída

    while (curr_visit <= network.getNumVertex()) {
        if (curr_visit == network.getNumVertex()) {
            for (auto edge : currVertex->getAdj()) {
                if (edge->getDest()->getInfo().getId() == start) {
                    ans += edge->getWeight();
                    path.push_back(start);
                    finished = true;
                }
            }
            if (!finished) {
                if (!path.empty()) {
                    int backtrackedNode = path.back();
                    currVertex->setVisited(false);
                    path.pop_back();
                    backtrackedNodes.insert(backtrackedNode);
                    if (!path.empty()) {
                        int lastVertexId = path.back();
                        currVertex = network.findVertex(Node(lastVertexId));
                        currVertex->setVisited(false);
                        curr_visit--;
                        backtracks++;
                    } else {
                        return std::numeric_limits<double>::infinity();
                    }
                }
                continue;
            }
        }

        if (finished)
            break;

        double minDistance = numeric_limits<double>::max();
        Vertex<Node>* nextVertex = nullptr;
        for (auto edge : currVertex->getAdj()) {
            if (edge->getWeight() < minDistance && !edge->getDest()->isVisited() &&
            backtrackedNodes.find(edge->getDest()->getInfo().getId()) == backtrackedNodes.end()) { // não se visitam os vértices sem saída
                minDistance = edge->getWeight();
                nextVertex = edge->getDest();
            }
        }
        if (nextVertex == nullptr) {
            if (!path.empty()) {
                int backtrackedNode = path.back();
                currVertex->setVisited(false);
                path.pop_back();
                backtrackedNodes.insert(backtrackedNode);
                if (!path.empty()) {
                    int lastVertexId = path.back();
                    currVertex = network.findVertex(Node(lastVertexId));
                    currVertex->setVisited(false);
                    curr_visit--;
                    backtracks++;
                } else {
                    return std::numeric_limits<double>::infinity();
                }
            }
            continue;
        }

        ans += minDistance;
        path.push_back(nextVertex->getInfo().getId());
        curr_visit++;
        nextVertex->setVisited(true);
        currVertex = nextVertex;
        backtrackedNodes.clear(); // novo caminho começou, podemos voltar a visitar estes vértices.
    }
    backs = backtracks;
    return ans;
}

string Algorithms::getNodeFile() {
    return this->nodeFile;
}

string Algorithms::getEdgeFile() {
    return this->edgeFile;
}

void Algorithms::resetNetwork() {
    for (auto v : network.getVertexSet()){
        v.second->setVisited(false);
        v.second->setProcesssing(false);
    }
}

double Algorithms::dijkstra(Vertex<Node> *source, Vertex<Node> *dest, vector<int> &path) {
    // Initialize the distance to all vertices to infinity and the distance to the source to 0
    double res=0;
    for (auto vertex : network.getVertexSet()) {
        vertex.second->setDist(INT_MAX);
        vertex.second->setPath(nullptr); // clear previous paths
        vertex.second->setProcesssing(false);
    }
    source->setDist(0);

    // Create a priority queue and insert all vertices
    MutablePriorityQueue<Vertex<Node> > myq_queue;
    myq_queue.insert(source);

    while (!myq_queue.empty()) {
        // Extract the vertex with the minimum distance
        auto u = myq_queue.extractMin();
        u->setProcesssing(true);

        // Stop if we reached the destination
        if (u == dest) break;

        // For each adjacent vertex of u
        for (auto edge : u->getAdj()) {
            Vertex<Node> *v = edge->getDest();
            int newDist = u->getDist() + edge->getWeight();

            // If a shorter path to v is found
            if (!v->isProcessing() && newDist < v->getDist()) {
                v->setDist(newDist);
                v->setPath(edge); // set the path to reach v
                myq_queue.insert(v);
            }
        }
    }

    // Reconstruct the shortest path from source to dest
    path.clear();
    Vertex<Node> *v = dest;
    while (v != nullptr) {
        path.push_back(v->getInfo().getId()); // assuming getInfo returns the node or the node's identifier
        auto edge = v->getPath();
        if (edge == nullptr) break;
        res+=edge->getWeight();
        if(edge->getOrig()== nullptr){
            cout<<"erro";
        }
        v = edge->getOrig();
    }
    std::reverse(path.begin(), path.end());
    return res;
}
void Algorithms::MakeGraphComeplete(){
    vector<int> path;
    set<pair<int, int>> processedPairs;

    for (auto ver1 : network.getVertexSet()) {
        cout<<ver1.second->getInfo().getId()<<endl;
        for (auto ver2 : network.getVertexSet()) {
            int id1 = ver1.second->getInfo().getId();
            int id2 = ver2.second->getInfo().getId();

            if (id1 < id2) {
                pair<int, int> vertexPair = make_pair(id1, id2);

                if (processedPairs.find(vertexPair) == processedPairs.end()) {
                    double dist = dijkstra(ver1.second, ver2.second, path);
                    network.addBidirectionalEdge(ver1.second->getInfo(), ver2.second->getInfo(), dist);
                    processedPairs.insert(vertexPair);
                }
            }
        }
    }
}


double Algorithms::tspDijkstraApprox(vector<int> &path, int start) {
    double ans = 0;

    cout<<path.size()<<endl;
    auto v=network.findVertex(Node(start));
    for( auto ver : network.getVertexSet()){
        ver.second->setVisited(false);
    }
    int numVertex = network.getNumVertex();
    cout<<numVertex<<endl;
    int cur=1;
    path.push_back(start);
    while( cur <numVertex){
        v->setVisited(true);
        double  mino=DBL_MAX;
        auto next=v;
        for( auto edge: v->getAdj()){
            if(edge->getDest()->isVisited()==false && edge->getWeight()<mino){
                next=edge->getDest();
                mino=edge->getWeight();
            }
        }
        if(next != v){
            ans+=mino;
            path.push_back(next->getInfo().getId());
            cur++;
            v=next;
        }
        else{
           for( auto ver : network.getVertexSet()){
               if(ver.second->isVisited()==false){
                   path.push_back(ver.second->getInfo().getId());
                   vector<int> dummy;
                   ans+=dijkstra(v,ver.second,dummy);

                   v=ver.second;
                   cur++;
                   break;
               }
            }
        }
    }
    return ans;
}