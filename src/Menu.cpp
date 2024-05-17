#include "Menu.h"

using namespace std;

void Menu::resetColor() {
    cout << "\033[0m";
}

void Menu::setColorRed() {
    cout << "\033[0;31m";
}

void Menu::setColorCyan() {
    cout << "\033[0;36m";
}

void Menu::clearScreen() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}

Menu::Menu() : manager("", "") {}

int Menu::getValidInt() {
    int number;
    cin >> number;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter an integer: ";
        std::cin >> number;
    }
    return number;
}

void Menu::start() {
    loadGraph();
    string option;
    while (true) {
        cout << "\nWhat do you want to do?\n";
        cout
                << "1) Select another graph\n2) Run an algorithm\n0) Exit the program\n";
        cin >> option;
        if (option == "1") {
            loadGraph();
        } else if (option == "2") {
            chooseAlgorithm();
        } else if (option == "0") {
            exit(0);
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }

}

void Menu::printPath(const vector<int> &path) {
    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i != path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

Algorithms Menu::chooseGraphType() {
    clearScreen();
    string option;
    string filename;
    while (true) {
        cout << "\nWhat type of graphs do you want to choose?\n";
        cout
                << "1) Small graphs\n2) Medium Graphs\n3) Large Graphs\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            filename = selectSmallGraph();
            if (filename.empty()) {
                clearScreen();
                continue;
            }
            return {"", filename};
        } else if (option == "2") {
            filename = selectMediumGraph();
            if (filename.empty()) {
                clearScreen();
                continue;
            }
            return {"../data/Extra_Fully_Connected_Graphs/nodes.csv", filename};
        } else if (option == "3") {
            pair<string, string> files = selectLargeGraph();
            if (files.first.empty() || files.second.empty()) {
                clearScreen();
                continue;
            }
            return {files.first, files.second};
        } else if (option == "0") {
            break;
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
    return {"", ""};
}

void Menu::loadGraph() {
    manager = chooseGraphType();
    if (manager.getNodeFile().empty() && manager.getEdgeFile().empty()) {
        return;
    }
    cout << "Edge file: " << manager.getEdgeFile() << "\n";
    cout << "Node file: " << manager.getNodeFile() << "\n";
    manager.readEdges();
    manager.readNodes();
}

void Menu::chooseAlgorithm() {
    if (manager.getEdgeFile().empty() && manager.getNodeFile().empty()) {
        setColorRed();
        cout << "No valid graph has been selected.\n";
        resetColor();
        return;
    }
    clearScreen();
    string option;
    while (true) {
        cout << "\nWhat algorithm do you want to run?\n";
        cout
                << "1) Backtracking\n2) Triangular Approximation\n3) Nearest Neighbour\n4) Optimized Nearest Neighbour\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            vector<int> path;
            double distance = manager.tspBacktracking(path);
            cout << "Total distance: " << distance << endl;
            printPath(path);
        } else if (option == "2") {
            vector<int> path;
            double distance = manager.tspTriangularApprox(path);
            cout << "Total distance: " << distance << endl;
            printPath(path);
        } else if (option == "3") {

            vector<int> path;
            double distance = manager.tspNearestNeighbour(path);
            cout << "Total distance: " << distance << endl;
            printPath(path);
        } else if (option == "4") {
            cout << "What node do you want to choose as the starting node?\n";
            int start = getValidInt();
            vector<int> path;
            double distance = manager.tspModifiedNearestNeighbour(path, start);
            cout << "Total distance: " << distance << endl;
            printPath(path);
        } else if (option == "0") {
            break;
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}


string Menu::selectSmallGraph() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nWhat graph do you want to choose?\n";
        cout
                << "1) Shipping graph\n2) Stadiums graph\n3) Tourism\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            return "../data/Toy-Graphs/shipping.csv";
        } else if (option == "2") {
            return "../data/Toy-Graphs/stadiums.csv";
        } else if (option == "3") {
            return "../data/Toy-Graphs/tourism.csv";
        } else if (option == "0") {
            return "";
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}

string Menu::selectMediumGraph() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nHow many edges do you want to choose?\n";
        cout
                << "1) 25\n2) 50\n3) 75\n4) 100\n5) 200\n6) 300\n7) 400\n8) 500\n9) 600\n10) 700\n11) 800\n12) 900\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            return "../data/Extra_Fully_Connected_Graphs/edges_25.csv";
        } else if (option == "2") {
            return "../data/Extra_Fully_Connected_Graphs/edges_50.csv";
        } else if (option == "3") {
            return "../data/Extra_Fully_Connected_Graphs/edges_75.csv";
        } else if (option == "4") {
            return "../data/Extra_Fully_Connected_Graphs/edges_100.csv";
        } else if (option == "5") {
            return "../data/Extra_Fully_Connected_Graphs/edges_200.csv";
        } else if (option == "6") {
            return "../data/Extra_Fully_Connected_Graphs/edges_300.csv";
        } else if (option == "7") {
            return "../data/Extra_Fully_Connected_Graphs/edges_400.csv";
        } else if (option == "8") {
            return "../data/Extra_Fully_Connected_Graphs/edges_500.csv";
        } else if (option == "9") {
            return "../data/Extra_Fully_Connected_Graphs/edges_600.csv";
        } else if (option == "10") {
            return "../data/Extra_Fully_Connected_Graphs/edges_700.csv";
        } else if (option == "11") {
            return "../data/Extra_Fully_Connected_Graphs/edges_800.csv";
        } else if (option == "12") {
            return "../data/Extra_Fully_Connected_Graphs/edges_900.csv";
        } else if (option == "0") {
            return "";
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}

pair<string, string> Menu::selectLargeGraph() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nHow many edges do you want to choose?\n";
        cout
                << "1) Graph 1 (~500K edges)\n2) Graph 2 (~4M edges)\n3) Graph 3 (~10M edges)\n0) Exit\n";
        cin >> option;
        if (option == "1") {
            return {"../data/Real-world Graphs/graph1/nodes.csv", "../data/Real-world Graphs/graph1/edges.csv"};
        } else if (option == "2") {
            return {"../data/Real-world Graphs/graph2/nodes.csv", "../data/Real-world Graphs/graph2/edges.csv"};
        } else if (option == "3") {
            return {"../data/Real-world Graphs/graph3/nodes.csv", "../data/Real-world Graphs/graph3/edges.csv"};
        } else if (option == "0") {
            return {"", ""};
        } else {
            setColorRed();
            cout << "Invalid option, please choose again.\n";
            resetColor();
        }
    }
}