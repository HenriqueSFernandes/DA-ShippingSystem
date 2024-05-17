#ifndef SHIPPING_SYSTEM_MENU_H
#define SHIPPING_SYSTEM_MENU_H

#include <iostream>
#include <string>
#include "Algorithms.h"

class Menu {
private:
    /**
     * @brief An instance of the Algorithms class.
     *
     * This instance, named manager, is used to manage the algorithms that are used in the Menu class.
     * It provides access to the various algorithms and methods defined in the Algorithms class.
     */
    Algorithms manager;
public:

    /**
     * @brief Menu constructor.
     *
     * This constructor initializes the manager member of the Menu class.
     * The manager is an instance of the Algorithms class, which is used to manage the algorithms that are used in the Menu class.
     * It provides access to the various algorithms and methods defined in the Algorithms class.
     *
     * The manager is initialized with two empty strings as parameters. These strings represent the filenames of the nodes and edges of the graph that the manager will handle.
     * An empty string indicates that no file has been selected yet.
     */
    Menu();

    /**
     * @brief Resets the console text color to default.
     *
     * This function uses an ANSI escape code to reset the console text color.
     * The escape code "\033[0m" resets all attributes, including color, back to their defaults.
     * This function is typically used after a call to a function that changes the color to ensure that subsequent console output is not affected by the color change.
     */
    static void resetColor();

    /**
     * @brief Sets the console text color to red.
     *
     * This function uses an ANSI escape code to set the console text color to red.
     * The escape code "\033[0;31m" sets the text color to red.
     * This function is typically used to highlight error messages or other important text.
     */
    static void setColorRed();

    /**
     * @brief Sets the console text color to cyan.
     *
     * This function uses an ANSI escape code to set the console text color to cyan.
     * The escape code "\033[0;36m" sets the text color to cyan.
     * This function is typically used to highlight informational messages or other non-critical text.
     */
    static void setColorCyan();

    /**
     * @brief Clears the console screen.
     *
     * This function uses the system() function to execute a command in the system shell.
     * The command that is executed depends on the operating system.
     * If the operating system is Windows, the command "cls" is executed.
     * If the operating system is not Windows (e.g., Linux, macOS), the command "clear" is executed.
     */
    static void clearScreen();

    /**
     * @brief This function is the start point of the menu.
     */
    void start();

    /**
     * @brief This functions asks the user to choose what type of graph to load.
     */
    static Algorithms chooseGraphType();


    void chooseAlgorithm();

    /**
     * @brief This function is responsible for loading the graph data.
     *
     * It calls two methods from the `algorithms` object: `readEdges()` and `readNodes()`.
     * `readEdges()` is responsible for reading and processing the edge data from the selected graph file.
     * `readNodes()` is responsible for reading and processing the node data from the selected graph file.
     *
     * After this function is called, the graph data is loaded and ready for further processing.
     */
    void loadGraph();

    /**
     * @brief Allows the user to select a small graph.
     *
     * This function presents the user with a menu of small graphs to choose from.
     * The user can choose between a shipping graph, a stadiums graph, a tourism graph, or exit the menu.
     * The user's choice is read from the console input.
     *
     * If the user chooses a valid option (1, 2, or 3), the function returns the filename of the chosen graph.
     * If the user chooses to exit (option 0), the function returns an empty string.
     * If the user chooses an invalid option, the function displays an error message and prompts the user to choose again.
     *
     * @return The filename of the chosen graph, or an empty string if the user chooses to exit.
     */
    static std::string selectSmallGraph();

    /**
     * @brief Allows the user to select a medium graph.
     *
     * This function presents the user with a menu of medium graphs to choose from.
     * The user can choose between graphs with different numbers of edges, ranging from 25 to 900, or exit the menu.
     * The user's choice is read from the console input.
     *
     * If the user chooses a valid option (1 to 12), the function returns the filename of the chosen graph.
     * If the user chooses to exit (option 0), the function returns an empty string.
     * If the user chooses an invalid option, the function displays an error message and prompts the user to choose again.
     *
     * @return The filename of the chosen graph, or an empty string if the user chooses to exit.
     */
    static std::string selectMediumGraph();

    /**
     * @brief Allows the user to select a large graph.
     *
     * This function presents the user with a menu of large graphs to choose from.
     * The user can choose between graphs with different numbers of edges, ranging from ~500K to ~10M, or exit the menu.
     * The user's choice is read from the console input.
     *
     * If the user chooses a valid option (1 to 3), the function returns a pair of filenames of the chosen graph's nodes and edges.
     * If the user chooses to exit (option 0), the function returns a pair of empty strings.
     * If the user chooses an invalid option, the function displays an error message and prompts the user to choose again.
     *
     * @return A pair of filenames of the chosen graph's nodes and edges, or a pair of empty strings if the user chooses to exit.
     */
    static std::pair<std::string, std::string> selectLargeGraph();

    static void printPath(const vector<int>& path);

    static int getValidInt();
};


#endif //SHIPPING_SYSTEM_MENU_H
