#include "fcfs.h"
#include <algorithm>

FCFS::FCFS() : Scheduler() {
}

void FCFS::schedule() {
    reset();
    
    // Ordenar procesos por tiempo de llegada
    std::sort(processes.begin(), processes.end(), 
        [](const Process& a, const Process& b) {
            if (a.getArrivalTime() != b.getArrivalTime()) {
                return a.getArrivalTime() < b.getArrivalTime();
            }
            return a.getId() < b.getId();
        });
    
    currentTime = 0;
    
    for (auto& process : processes) {
        // Si el proceso aún no ha llegado, esperar hasta su tiempo de llegada
        if (currentTime < process.getArrivalTime()) {
            currentTime = process.getArrivalTime();
        }
        
        // Ejecutar el proceso hasta completarse
        executeProcess(process, currentTime, process.getBurstTime());
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

