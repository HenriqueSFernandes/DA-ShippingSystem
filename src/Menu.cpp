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

void Menu::chooseGraph() {
    clearScreen();
    string option;
    while (true) {
        cout << "\nWhat graph do you want to choose?\n";
        cout
                << "1) Disable reservoirs.\n2) Disable pumping stations.\n3) Disable pipes.\n4) Calculate the impact of the changes.\n5) Reset\n0) Exit.\n";
        cin >> option;
    }
}
