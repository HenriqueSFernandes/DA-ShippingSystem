#ifndef SHIPPING_SYSTEM_MENU_H
#define SHIPPING_SYSTEM_MENU_H

#include <iostream>

class Menu {

    /**
     * @brief Sets the terminal text color to default.
     */
    static void resetColor();

    /**
     * @brief Sets the terminal text color to red.
     */
    static void setColorRed();

    /**
     * @brief Sets the terminal text color to cyan.
     */
    static void setColorCyan();

    /**
     * @brief This function clear the screen. It should work on all platforms.
     */
    static void clearScreen();

    void chooseGraph();
};


#endif //SHIPPING_SYSTEM_MENU_H
