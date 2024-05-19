#include <iomanip>
#include "src/Algorithms.h"
#include "src/Menu.h"

int main() {
//    string nodeFile = "";
   string edgeFile = "../data/Toy-Graphs/shipping.csv";
//    string nodeFile = "../data/Real-world Graphs/graph1/nodes.csv";
//    string edgeFile = "../data/Real-world Graphs/graph1/edges.csv";

    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    //string nodeFile = "../data/Real-world Graphs/graph3/nodes.csv";
    //string edgeFile = "../data/Real-world Graphs/graph3/edges.csv";

  Algorithms manager = Algorithms("", edgeFile);
  manager.readEdges();
  vector<int> path;

  manager.MakeGraphComeplete();
  auto s=manager.network.getVertexSet().at(0);
  int backs=0;
  cout<<manager.tspModifiedNearestNeighbour( path, backs,0);

    return 0;
}
