#ifndef INTERFACE_H
#define INTERFACE_H

#include "../Core/process.h"
#include "../Core/scheduler.h"
#include <vector>
#include <string>

class UserInterface {
public:
    static void printMainMenu();
    static int getUserChoice();
    static void printAlgorithmMenu();
    static Process createProcessManually(int id);
    static void printProcessList(const std::vector<Process>& processes);
    static void clearScreen();
    static void waitForEnter();
    static int getIntInput(const std::string& prompt);
};

#endif // INTERFACE_H

