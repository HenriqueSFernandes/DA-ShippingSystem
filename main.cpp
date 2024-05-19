#include <iomanip>
#include "src/Algorithms.h"
#include "src/Menu.h"

int main() {
//    string nodeFile = "";
//    string nodeFile = "../data/Real-world Graphs/graph1/nodes.csv";
  string edgeFile = "../data/Real-world Graphs/graph3/edges.csv";
//string edgeFile = "../data/Toy-Graphs/shipping.csv";

    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    //string nodeFile = "../data/Real-world Graphs/graph1/nodes.csv";
   // string edgeFile = "../data/Real-world Graphs/graph1/edges.csv";

  Algorithms manager = Algorithms("", edgeFile);
  manager.readEdges();
  vector<int> path;

  int backs=0;
  cout<<manager.tspDijkstraApprox( path,0);

    return 0;
}
