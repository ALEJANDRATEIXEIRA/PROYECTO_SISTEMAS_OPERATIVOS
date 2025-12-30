#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <vector>
#include <string>

class Scheduler {
protected:
    std::vector<Process> processes;
    std::vector<Process> originalProcesses;  // Copia para preservar datos originales
    int currentTime;
    std::vector<std::pair<int, int>> ganttChart;  // {proceso_id, tiempo}
    
public:
    Scheduler();
    virtual ~Scheduler() = default;
    
    // Métodos principales
    void addProcess(const Process& process);
    void addProcesses(const std::vector<Process>& processes);
    void clearProcesses();
    
    // Método virtual que cada algoritmo debe implementar
    virtual void schedule() = 0;
    
    // Getters
    std::vector<Process> getProcesses() const { return originalProcesses; }
    std::vector<std::pair<int, int>> getGanttChart() const { return ganttChart; }
    int getCurrentTime() const { return currentTime; }
    
    // Métodos de utilidad
    void reset();
    virtual std::string getName() const = 0;
    
protected:
    // Métodos auxiliares para los algoritmos
    void executeProcess(Process& process, int startTime, int duration);
    void addToGanttChart(int processId, int time);
};

#endif // SCHEDULER_H

