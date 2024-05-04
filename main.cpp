//
// Created by memechanic on 04-05-2024.
//

#include "src/Algorithms.h"

int main() {
    string nodeFile = "../data/Extra_Fully_Connected_Graphs/nodes.csv";
    string edgeFile = "../data/Extra_Fully_Connected_Graphs/edges_900.csv";

    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    //string nodeFile = "../data/Real-world Graphs/graph3/nodes.csv";
    //string edgeFile = "../data/Real-world Graphs/graph3/edges.csv";

    Algorithms manager = Algorithms(nodeFile, edgeFile);

    manager.readNodes();
    manager.readEdges();
    return 0;
}
