#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "Core/process.h"
#include "Core/scheduler.h"
#include "algorithms/fcfs.h"
#include "algorithms/sjf.h"
#include "algorithms/round_robin.h"
#include "algorithms/priority.h"
#include "metrics.h"
#include "Utils/file_handler.h"
#include "UI/interface.h"

int main() {
    std::vector<Process> processes;
    bool running = true;
    
    // Crear directorio de casos de prueba si no existe
    FileHandler::createDefaultTestFiles();
    
    while (running) {
        UserInterface::clearScreen();
        UserInterface::printMainMenu();
        
        int choice = UserInterface::getUserChoice();
        
        switch (choice) {
            case 1: {
                // Cargar procesos desde archivo
                std::string filename;
                std::cout << "Ingrese el nombre del archivo (ej: test_cases/conjunto1.txt): ";
                std::cin >> filename;
                processes = FileHandler::loadProcessesFromFile(filename);
                
                if (!processes.empty()) {
                    std::cout << "\n✓ Se cargaron " << processes.size() << " procesos correctamente.\n";
                } else {
                    std::cout << "\n✗ Error al cargar procesos.\n";
                }
                UserInterface::waitForEnter();
                break;
            }
            
            case 2: {
                // Crear procesos manualmente
                processes.clear();
                int numProcesses = UserInterface::getIntInput("¿Cuántos procesos desea crear? ");
                
                for (int i = 1; i <= numProcesses; i++) {
                    Process p = UserInterface::createProcessManually(i);
                    processes.push_back(p);
                }
                
                std::cout << "\n✓ Se crearon " << processes.size() << " procesos correctamente.\n";
                UserInterface::waitForEnter();
                break;
            }
            
            case 3: {
                // Ejecutar simulación
                if (processes.empty()) {
                    std::cout << "\n✗ No hay procesos cargados. Por favor cargue o cree procesos primero.\n";
                    UserInterface::waitForEnter();
                    break;
                }
                
                UserInterface::clearScreen();
                UserInterface::printAlgorithmMenu();
                int algoChoice = UserInterface::getUserChoice();
                
                std::unique_ptr<Scheduler> scheduler;
                std::string algoName;
                
                switch (algoChoice) {
                    case 1: {
                        scheduler = std::make_unique<FCFS>();
                        algoName = scheduler->getName();
                        break;
                    }
                    case 2: {
                        scheduler = std::make_unique<SJF>();
                        algoName = scheduler->getName();
                        break;
                    }
                    case 3: {
                        int quantum = UserInterface::getIntInput("Ingrese el quantum para Round Robin: ");
                        scheduler = std::make_unique<RoundRobin>(quantum);
                        algoName = scheduler->getName();
                        break;
                    }
                    case 4: {
                        scheduler = std::make_unique<PriorityScheduler>(false);
                        algoName = scheduler->getName();
                        break;
                    }
                    case 5: {
                        scheduler = std::make_unique<PriorityScheduler>(true);
                        algoName = scheduler->getName();
                        break;
                    }
                    default:
                        std::cout << "\n✗ Opción inválida.\n";
                        UserInterface::waitForEnter();
                        continue;
                }
                
                if (scheduler) {
                    scheduler->addProcesses(processes);
                    scheduler->schedule();
                    
                    UserInterface::clearScreen();
                    std::cout << "\n" << std::string(80, '=') << "\n";
                    std::cout << "RESULTADOS DE LA SIMULACIÓN: " << algoName << "\n";
                    std::cout << std::string(80, '=') << "\n";
                    
                    std::vector<Process> resultProcesses = scheduler->getProcesses();
                    MetricsCalculator::printProcessMetrics(resultProcesses);
                    
                    int totalTime = scheduler->getCurrentTime();
                    SystemMetrics metrics = MetricsCalculator::calculateSystemMetrics(resultProcesses, totalTime);
                    MetricsCalculator::printSystemMetrics(metrics);
                    
                    MetricsCalculator::printGanttChart(scheduler->getGanttChart());
                    
                    UserInterface::waitForEnter();
                }
                break;
            }
            
            case 4: {
                // Ver procesos actuales
                UserInterface::clearScreen();
                UserInterface::printProcessList(processes);
                UserInterface::waitForEnter();
                break;
            }
            
            case 5: {
                // Comparar todos los algoritmos
                if (processes.empty()) {
                    std::cout << "\n✗ No hay procesos cargados. Por favor cargue o cree procesos primero.\n";
                    UserInterface::waitForEnter();
                    break;
                }
                
                UserInterface::clearScreen();
                std::cout << "\n" << std::string(80, '=') << "\n";
                std::cout << "COMPARACIÓN DE TODOS LOS ALGORITMOS\n";
                std::cout << std::string(80, '=') << "\n\n";
                
                std::map<std::string, std::vector<Process>> results;
                std::map<std::string, int> totalTimes;
                
                // FCFS
                auto fcfs = std::make_unique<FCFS>();
                fcfs->addProcesses(processes);
                fcfs->schedule();
                results[fcfs->getName()] = fcfs->getProcesses();
                totalTimes[fcfs->getName()] = fcfs->getCurrentTime();
                
                // SJF
                auto sjf = std::make_unique<SJF>();
                sjf->addProcesses(processes);
                sjf->schedule();
                results[sjf->getName()] = sjf->getProcesses();
                totalTimes[sjf->getName()] = sjf->getCurrentTime();
                
                // Round Robin (quantum = 4)
                int quantum = 4;
                auto rr = std::make_unique<RoundRobin>(quantum);
                rr->addProcesses(processes);
                rr->schedule();
                results[rr->getName()] = rr->getProcesses();
                totalTimes[rr->getName()] = rr->getCurrentTime();
                
                // Priority (sin desalojo)
                auto priority1 = std::make_unique<PriorityScheduler>(false);
                priority1->addProcesses(processes);
                priority1->schedule();
                results[priority1->getName()] = priority1->getProcesses();
                totalTimes[priority1->getName()] = priority1->getCurrentTime();
                
                // Comparar
                MetricsCalculator::compareAlgorithms(results, totalTimes);
                
                UserInterface::waitForEnter();
                break;
            }
            
            case 6: {
                // Salir
                std::cout << "\n¡Gracias por usar el simulador!\n";
                running = false;
                break;
            }
            
            default:
                std::cout << "\n✗ Opción inválida. Por favor seleccione una opción válida.\n";
                UserInterface::waitForEnter();
                break;
        }
    }
    
    return 0;
}

