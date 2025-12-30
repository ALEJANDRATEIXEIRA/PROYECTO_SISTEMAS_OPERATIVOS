#include "sjf.h"
#include <algorithm>
#include <climits>

SJF::SJF() : Scheduler() {
}

Process* SJF::getShortestJob(int currentTime) {
    Process* shortest = nullptr;
    int shortestBurst = INT_MAX;
    
    for (auto& process : processes) {
        if (process.getState() != ProcessState::TERMINATED &&
            process.getArrivalTime() <= currentTime) {
            if (process.getBurstTime() < shortestBurst) {
                shortestBurst = process.getBurstTime();
                shortest = &process;
            } else if (process.getBurstTime() == shortestBurst && shortest != nullptr) {
                // En caso de empate, elegir el que llegó primero
                if (process.getArrivalTime() < shortest->getArrivalTime() ||
                    (process.getArrivalTime() == shortest->getArrivalTime() &&
                     process.getId() < shortest->getId())) {
                    shortest = &process;
                }
            }
        }
    }
    
    return shortest;
}

void SJF::schedule() {
    reset();
    currentTime = 0;
    
    int completed = 0;
    int totalProcesses = processes.size();
    
    while (completed < totalProcesses) {
        Process* next = getShortestJob(currentTime);
        
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
            // Ejecutar el proceso más corto hasta completarse
            executeProcess(*next, currentTime, next->getBurstTime());
            completed++;
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

