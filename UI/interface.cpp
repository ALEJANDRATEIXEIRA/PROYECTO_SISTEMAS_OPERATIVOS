#include "interface.h"
#include <iostream>
#include <limits>
#include <iomanip>
#include <cstdlib>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void UserInterface::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UserInterface::printMainMenu() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  SIMULADOR DE ALGORITMOS DE PLANIFICACIÓN DE CPU\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "1. Cargar procesos desde archivo\n";
    std::cout << "2. Crear procesos manualmente\n";
    std::cout << "3. Ejecutar simulación\n";
    std::cout << "4. Ver procesos actuales\n";
    std::cout << "5. Comparar todos los algoritmos\n";
    std::cout << "6. Salir\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "Seleccione una opción: ";
}

int UserInterface::getUserChoice() {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return choice;
}

void UserInterface::printAlgorithmMenu() {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  SELECCIONAR ALGORITMO DE PLANIFICACIÓN\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "1. FCFS (First Come First Served)\n";
    std::cout << "2. SJF (Shortest Job First)\n";
    std::cout << "3. Round Robin\n";
    std::cout << "4. Prioridades (Sin Desalojo)\n";
    std::cout << "5. Prioridades (Con Desalojo)\n";
    std::cout << std::string(60, '=') << "\n";
    std::cout << "Seleccione un algoritmo: ";
}

Process UserInterface::createProcessManually(int id) {
    std::cout << "\n--- Crear Proceso P" << id << " ---\n";
    
    int arrivalTime = getIntInput("Tiempo de llegada: ");
    int burstTime = getIntInput("Tiempo de ráfaga: ");
    int priority = getIntInput("Prioridad (menor número = mayor prioridad): ");
    
    return Process(id, arrivalTime, burstTime, priority);
}

void UserInterface::printProcessList(const std::vector<Process>& processes) {
    if (processes.empty()) {
        std::cout << "\nNo hay procesos cargados.\n";
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "PROCESOS CARGADOS\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << std::left 
              << std::setw(12) << "Proceso"
              << std::setw(15) << "Llegada"
              << std::setw(15) << "Ráfaga"
              << std::setw(15) << "Prioridad"
              << "\n";
    std::cout << std::string(80, '-') << "\n";
    
    for (const auto& process : processes) {
        std::cout << std::left
                  << std::setw(12) << ("P" + std::to_string(process.getId()))
                  << std::setw(15) << process.getArrivalTime()
                  << std::setw(15) << process.getBurstTime()
                  << std::setw(15) << process.getPriority()
                  << "\n";
    }
    std::cout << std::string(80, '=') << "\n";
}

void UserInterface::waitForEnter() {
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
}

int UserInterface::getIntInput(const std::string& prompt) {
    int value;
    std::cout << prompt;
    std::cin >> value;
    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Entrada inválida. Por favor ingrese un número: ";
        std::cin >> value;
    }
    return value;
}

