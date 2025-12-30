#include "metrics.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>
#include <limits>

SystemMetrics MetricsCalculator::calculateSystemMetrics(const std::vector<Process>& processes, int totalTime) {
    SystemMetrics metrics;
    
    if (processes.empty()) {
        return metrics;
    }
    
    double sumTurnaround = 0;
    double sumWaiting = 0;
    double sumResponse = 0;
    int totalBurstTime = 0;
    
    for (const auto& process : processes) {
        sumTurnaround += process.getTurnaroundTime();
        sumWaiting += process.getWaitingTime();
        sumResponse += process.getResponseTime();
        totalBurstTime += process.getBurstTime();
    }
    
    metrics.averageTurnaroundTime = sumTurnaround / processes.size();
    metrics.averageWaitingTime = sumWaiting / processes.size();
    metrics.averageResponseTime = sumResponse / processes.size();
    
    if (totalTime > 0) {
        metrics.cpuUtilization = (static_cast<double>(totalBurstTime) / totalTime) * 100.0;
    }
    
    return metrics;
}

void MetricsCalculator::printProcessMetrics(const std::vector<Process>& processes) {
    std::cout << "\n" << std::string(120, '=') << "\n";
    std::cout << "MÉTRICAS POR PROCESO\n";
    std::cout << std::string(120, '=') << "\n";
    
    std::cout << std::left 
              << std::setw(12) << "Proceso"
              << std::setw(15) << "Llegada"
              << std::setw(15) << "Ráfaga"
              << std::setw(15) << "Prioridad"
              << std::setw(15) << "T. Retorno"
              << std::setw(15) << "T. Espera"
              << std::setw(15) << "T. Respuesta"
              << std::setw(15) << "T. Finalización"
              << "\n";
    
    std::cout << std::string(120, '-') << "\n";
    
    for (const auto& process : processes) {
        std::cout << std::left
                  << std::setw(12) << ("P" + std::to_string(process.getId()))
                  << std::setw(15) << process.getArrivalTime()
                  << std::setw(15) << process.getBurstTime()
                  << std::setw(15) << process.getPriority()
                  << std::setw(15) << process.getTurnaroundTime()
                  << std::setw(15) << process.getWaitingTime()
                  << std::setw(15) << process.getResponseTime()
                  << std::setw(15) << process.getFinishTime()
                  << "\n";
    }
    
    std::cout << std::string(120, '=') << "\n\n";
}

void MetricsCalculator::printSystemMetrics(const SystemMetrics& metrics) {
    std::cout << "\n" << std::string(120, '=') << "\n";
    std::cout << "MÉTRICAS DEL SISTEMA\n";
    std::cout << std::string(120, '=') << "\n";
    
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tiempo Promedio de Retorno: " << metrics.averageTurnaroundTime << "\n";
    std::cout << "Tiempo Promedio de Espera:   " << metrics.averageWaitingTime << "\n";
    std::cout << "Tiempo Promedio de Respuesta: " << metrics.averageResponseTime << "\n";
    std::cout << "Utilización de CPU:          " << metrics.cpuUtilization << "%\n";
    std::cout << std::string(120, '=') << "\n\n";
}

void MetricsCalculator::printGanttChart(const std::vector<std::pair<int, int>>& ganttChart) {
    if (ganttChart.empty()) {
        std::cout << "\nNo hay datos para mostrar el Diagrama de Gantt.\n\n";
        return;
    }
    
    std::cout << "\n" << std::string(120, '=') << "\n";
    std::cout << "DIAGRAMA DE GANTT\n";
    std::cout << std::string(120, '=') << "\n";
    
    // Calcular ancho mínimo para cada entrada
    const int MIN_WIDTH = 4;  // Ancho mínimo para mostrar el proceso
    
    // Línea superior
    std::cout << "|";
    for (const auto& entry : ganttChart) {
        int width = std::max(MIN_WIDTH, entry.second * 2);
        std::cout << std::string(width, '-') << "|";
    }
    std::cout << "\n";
    
    // Procesos
    std::cout << "|";
    for (const auto& entry : ganttChart) {
        int width = std::max(MIN_WIDTH, entry.second * 2);
        std::string processName = "P" + std::to_string(entry.first);
        int padding = std::max(0, (width - static_cast<int>(processName.length())) / 2);
        int totalWidth = width - 1;
        int remainingSpace = std::max(0, totalWidth - padding - static_cast<int>(processName.length()));
        std::cout << std::string(padding, ' ') << processName 
                  << std::string(remainingSpace, ' ') << "|";
    }
    std::cout << "\n";
    
    // Línea inferior
    std::cout << "|";
    for (const auto& entry : ganttChart) {
        int width = std::max(MIN_WIDTH, entry.second * 2);
        std::cout << std::string(width, '-') << "|";
    }
    std::cout << "\n";
    
    // Tiempos
    int currentTime = 0;
    std::cout << currentTime;
    for (const auto& entry : ganttChart) {
        currentTime += entry.second;
        int width = std::max(MIN_WIDTH, entry.second * 2);
        std::string timeStr = std::to_string(currentTime);
        int spaceNeeded = std::max(1, width - static_cast<int>(timeStr.length()) + 1);
        std::cout << std::string(spaceNeeded, ' ') << timeStr;
    }
    std::cout << "\n";
    std::cout << std::string(120, '=') << "\n\n";
}

std::map<std::string, SystemMetrics> MetricsCalculator::compareAlgorithms(
    const std::map<std::string, std::vector<Process>>& results,
    const std::map<std::string, int>& totalTimes) {
    
    std::map<std::string, SystemMetrics> comparison;
    
    for (const auto& pair : results) {
        auto it = totalTimes.find(pair.first);
        int totalTime = (it != totalTimes.end()) ? it->second : 0;
        comparison[pair.first] = calculateSystemMetrics(pair.second, totalTime);
    }
    
    // Imprimir tabla comparativa
    std::cout << "\n" << std::string(120, '=') << "\n";
    std::cout << "COMPARACIÓN DE ALGORITMOS\n";
    std::cout << std::string(120, '=') << "\n";
    
    std::cout << std::left 
              << std::setw(30) << "Algoritmo"
              << std::setw(25) << "T. Retorno Promedio"
              << std::setw(25) << "T. Espera Promedio"
              << std::setw(25) << "Utilización CPU"
              << "\n";
    
    std::cout << std::string(120, '-') << "\n";
    
    for (const auto& pair : comparison) {
        std::cout << std::fixed << std::setprecision(2);
        std::cout << std::left
                  << std::setw(30) << pair.first
                  << std::setw(25) << pair.second.averageTurnaroundTime
                  << std::setw(25) << pair.second.averageWaitingTime
                  << std::setw(25) << pair.second.cpuUtilization << "%"
                  << "\n";
    }
    
    std::cout << std::string(120, '=') << "\n\n";
    
    // Determinar mejor algoritmo
    std::string bestAlgorithm = "";
    double minWaiting = std::numeric_limits<double>::max();
    
    for (const auto& pair : comparison) {
        if (pair.second.averageWaitingTime < minWaiting) {
            minWaiting = pair.second.averageWaitingTime;
            bestAlgorithm = pair.first;
        }
    }
    
    if (!bestAlgorithm.empty()) {
        std::cout << "MEJOR ALGORITMO PARA ESTE CASO: " << bestAlgorithm 
                  << " (Menor tiempo promedio de espera: " << minWaiting << ")\n\n";
    }
    
    return comparison;
}

