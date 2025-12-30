#include "round_robin.h"
#include <queue>
#include <algorithm>

RoundRobin::RoundRobin(int quantum) : Scheduler(), quantum(quantum) {
}

void RoundRobin::schedule() {
    reset();
    currentTime = 0;
    
    // Ordenar procesos por tiempo de llegada
    std::sort(processes.begin(), processes.end(),
        [](const Process& a, const Process& b) {
            if (a.getArrivalTime() != b.getArrivalTime()) {
                return a.getArrivalTime() < b.getArrivalTime();
            }
            return a.getId() < b.getId();
        });
    
    std::queue<int> readyQueue;  // Índices de procesos en la cola
    std::vector<bool> inQueue(processes.size(), false);
    
    size_t processIndex = 0;
    int completed = 0;
    size_t totalProcesses = processes.size();
    
    // Agregar procesos que llegan al tiempo 0
    while (processIndex < processes.size() && 
           processes[processIndex].getArrivalTime() <= currentTime) {
        readyQueue.push(static_cast<int>(processIndex));
        inQueue[processIndex] = true;
        processIndex++;
    }
    
    while (completed < static_cast<int>(totalProcesses)) {
        if (readyQueue.empty()) {
            // Si no hay procesos en la cola, avanzar al siguiente tiempo de llegada
            if (processIndex < processes.size()) {
                currentTime = processes[processIndex].getArrivalTime();
                while (processIndex < processes.size() && 
                       processes[processIndex].getArrivalTime() <= currentTime) {
                    readyQueue.push(static_cast<int>(processIndex));
                    inQueue[processIndex] = true;
                    processIndex++;
                }
            } else {
                break;
            }
        } else {
            int currentIndex = readyQueue.front();
            readyQueue.pop();
            inQueue[currentIndex] = false;
            
            Process& currentProcess = processes[currentIndex];
            
            // Ejecutar por el quantum o hasta que termine
            int executionTime = std::min(quantum, currentProcess.getRemainingTime());
            int startTime = currentTime;
            
            // Agregar procesos que llegan durante la ejecución
            while (processIndex < processes.size() && 
                   processes[processIndex].getArrivalTime() <= currentTime + executionTime) {
                if (!inQueue[processIndex]) {
                    readyQueue.push(static_cast<int>(processIndex));
                    inQueue[processIndex] = true;
                }
                processIndex++;
            }
            
            executeProcess(currentProcess, startTime, executionTime);
            
            // Si el proceso no ha terminado, agregarlo de nuevo a la cola
            if (currentProcess.getState() != ProcessState::TERMINATED) {
                readyQueue.push(static_cast<int>(currentIndex));
                inQueue[currentIndex] = true;
            } else {
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

