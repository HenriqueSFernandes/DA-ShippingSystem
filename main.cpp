//
// Created by memechanic on 04-05-2024.
//

#include <iomanip>
#include "src/Algorithms.h"

int main() {


    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    string nodeFile = "../data/Real-world Graphs/graph3/nodes.csv";
    string edgeFile = "../data/Real-world Graphs/graph3/edges.csv";

    Algorithms manager = Algorithms(nodeFile, edgeFile);

    manager.readEdges();
    manager.readNodes();
    vector<int> path;
    int backtracks;
    clock_t start, end;
    start = clock();
    //cout<<"RES IS "<<manager.tspTriangularAprox(path)<<endl;
    //cout<<"RES IS "<<manager.tspNearestNeighbour(path)<<endl;
    cout<<"RES IS "<<fixed<<setprecision(2)<<manager.tspTriangularAprox(path)<< endl ;

    end = clock();
    cout<<"here"<<endl;

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;


    return 0;
}
