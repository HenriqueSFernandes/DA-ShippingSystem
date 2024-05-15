#include <iomanip>
#include "src/Algorithms.h"

int main() {
    string nodeFile = "../data/Extra_Fully_Connected_Graphs/nodes.csv";
    string edgeFile = "../data/Extra_Fully_Connected_Graphs/edges_900.csv";

    //isto demora mais de 30 minutos no meu pc, tenham cuidado
    //string nodeFile = "../data/Real-world Graphs/graph3/nodes.csv";
    //string edgeFile = "../data/Real-world Graphs/graph3/edges.csv";

    Algorithms manager = Algorithms(nodeFile, edgeFile);

    manager.readEdges();
    manager.readNodes();
    vector<int> path;
    clock_t start, end;
    start = clock();
    //cout<<"RES IS "<<manager.tspTriangularAprox(path)<<endl;
    cout<<"RES IS "<<manager.tspNearestNeighbour(path)<<endl;
    end = clock();

    // Calculating total time taken by the program.
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed
         << time_taken << setprecision(5);
    cout << " sec " << endl;
    for(auto i : path){
        cout << i << " ";
    }
    return 0;
}
