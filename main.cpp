#include <iomanip>
#include "src/Algorithms.h"
#include "src/Menu.h"

int main() {

//    string nodeFile = "";
//    string edgeFile = "../data/Toy-Graphs/shipping.csv";
//    string nodeFile = "../data/Real-world Graphs/graph1/nodes.csv";
//    string edgeFile = "../data/Real-world Graphs/graph1/edges.csv";

    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    string nodeFile = "../data/Real-world Graphs/graph1/nodes.csv";
    string edgeFile = "../data/Real-world Graphs/graph1/edges.csv";

//    Algorithms manager = Algorithms(nodeFile, edgeFile);

//    manager.readEdges();
//    manager.readNodes();
//    vector<int> path;
//    clock_t start, end;
//    start = clock();
    //cout<<"RES IS "<<manager.tspTriangularAprox(path)<<endl;
//    cout<<"RES IS "<<manager.tspNearestNeighbour(path)<<endl;
//    end = clock();
//
//    // Calculating total time taken by the program.
//    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
//    cout << "Time taken by program is : " << fixed
//         << time_taken << setprecision(5);
//    cout << " sec " << endl;
//    for(auto i : path){
//        cout << i << " ";
//    }
//    double a = manager.tspTriangularAprox(path);
//    double a = manager.tspBacktracking(path);
//    cout << "distance: " << a << endl;
//    for (auto i: path) {
//        cout << i << "<";
//    }
    //cout<<"RES IS "<<manager.tspNearestNeighbour(path)<<endl;

//    cout<<"RES IS "<<manager.tspModifiedNearestNeighbour(path, 500)<<endl;
//    end = clock();

    Menu menu;
    menu.start();


    return 0;
}
