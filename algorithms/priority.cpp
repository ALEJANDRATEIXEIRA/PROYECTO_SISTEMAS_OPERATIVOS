#include "priority.h"
#include <algorithm>
#include <climits>

PriorityScheduler::PriorityScheduler(bool preemptive) 
    : Scheduler(), preemptive(preemptive) {
}

Process* PriorityScheduler::getHighestPriorityProcess(int currentTime) {
    Process* highest = nullptr;
    int highestPriority = INT_MAX;  // Menor número = mayor prioridad
    
    for (auto& process : processes) {
        if ((process.getState() != ProcessState::TERMINATED) &&
            process.getArrivalTime() <= currentTime) {
            if (process.getPriority() < highestPriority) {
                highestPriority = process.getPriority();
                highest = &process;
            } else if (process.getPriority() == highestPriority && highest != nullptr) {
                // En caso de empate, elegir el que llegó primero
                if (process.getArrivalTime() < highest->getArrivalTime() ||
                    (process.getArrivalTime() == highest->getArrivalTime() &&
                     process.getId() < highest->getId())) {
                    highest = &process;
                }
            }
        }
    }
    
    return highest;
}

void PriorityScheduler::schedule() {
    reset();
    currentTime = 0;
    
    if (preemptive) {
        // Algoritmo con desalojo (preemptive) - ejecución unidad por unidad
        int completed = 0;
        int totalProcesses = processes.size();
        Process* currentRunning = nullptr;
        
        while (completed < totalProcesses) {
            Process* next = getHighestPriorityProcess(currentTime);
            
            // Si hay un proceso diferente de mayor prioridad, cambiar
            if (next != nullptr && (currentRunning == nullptr || 
                next->getPriority() < currentRunning->getPriority())) {
                if (currentRunning != nullptr && currentRunning->getState() == ProcessState::RUNNING) {
                    currentRunning->setState(ProcessState::READY);
                }
                currentRunning = next;
                if (currentRunning->getState() == ProcessState::NEW || 
                    currentRunning->getState() == ProcessState::READY) {
                    currentRunning->setState(ProcessState::RUNNING);
                    currentRunning->setStartTime(currentTime);
                }
            } else if (currentRunning == nullptr && next != nullptr) {
                currentRunning = next;
                currentRunning->setState(ProcessState::RUNNING);
                currentRunning->setStartTime(currentTime);
            }
            
            if (currentRunning != nullptr) {
                // Ejecutar por 1 unidad de tiempo
                currentRunning->setExecutedTime(currentRunning->getExecutedTime() + 1);
                currentRunning->setRemainingTime(currentRunning->getRemainingTime() - 1);
                addToGanttChart(currentRunning->getId(), 1);
                currentTime++;
                
                if (currentRunning->getRemainingTime() == 0) {
                    currentRunning->setState(ProcessState::TERMINATED);
                    currentRunning->setFinishTime(currentTime);
                    currentRunning->calculateMetrics();
                    currentRunning = nullptr;
                    completed++;
                }
            } else {
                // No hay procesos listos, avanzar al siguiente tiempo de llegada
                int nextArrival = INT_MAX;
                for (const auto& p : processes) {
                    if (p.getState() != ProcessState::TERMINATED && 
                        p.getArrivalTime() > currentTime) {
                        nextArrival = std::min(nextArrival, p.getArrivalTime());
                    }
                }
                if (nextArrival != INT_MAX) {
                    currentTime = nextArrival;
                } else {
                    break;
                }
            }
        }
    } else {
        // Algoritmo sin desalojo (non-preemptive)
        int completed = 0;
        int totalProcesses = processes.size();
        
        while (completed < totalProcesses) {
            Process* next = getHighestPriorityProcess(currentTime);
            
            if (next == nullptr) {
                // No hay procesos listos, avanzar tiempo
                int nextArrival = INT_MAX;
                for (const auto& p : processes) {
                    if (p.getState() != ProcessState::TERMINATED && 
                        p.getArrivalTime() > currentTime) {
                        nextArrival = std::min(nextArrival, p.getArrivalTime());
                    }
                }
                if (nextArrival != INT_MAX) {
                    currentTime = nextArrival;
                } else {
                    break;
                }
            } else {
                // Ejecutar el proceso de mayor prioridad hasta completarse
                executeProcess(*next, currentTime, next->getBurstTime());
                completed++;
            }
        }
    }
    
    // Actualizar procesos originales con las métricas calculadas
    for (auto& original : originalProcesses) {
        for (const auto& updated : processes) {
            if (original.getId() == updated.getId()) {
                original = updated;
                break;
            }
        }
    }
}

