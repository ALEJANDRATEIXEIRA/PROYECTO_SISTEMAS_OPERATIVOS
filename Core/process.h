#ifndef PROCESS_H
#define PROCESS_H

#include <string>

enum class ProcessState {
    NEW,        // Nuevo
    READY,      // Listo
    RUNNING,    // Ejecutando
    TERMINATED  // Terminado
};

class Process {
private:
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    ProcessState state;
    
    // Tiempos calculados durante la simulación
    int startTime;          // Tiempo de primera ejecución
    int finishTime;         // Tiempo de finalización
    int waitingTime;        // Tiempo de espera
    int turnaroundTime;     // Tiempo de retorno
    int responseTime;       // Tiempo de respuesta
    int remainingTime;      // Tiempo restante de ejecución
    int executedTime;       // Tiempo ya ejecutado
    
public:
    // Constructor
    Process(int id, int arrivalTime, int burstTime, int priority);
    
    // Getters
    int getId() const { return id; }
    int getArrivalTime() const { return arrivalTime; }
    int getBurstTime() const { return burstTime; }
    int getPriority() const { return priority; }
    ProcessState getState() const { return state; }
    int getStartTime() const { return startTime; }
    int getFinishTime() const { return finishTime; }
    int getWaitingTime() const { return waitingTime; }
    int getTurnaroundTime() const { return turnaroundTime; }
    int getResponseTime() const { return responseTime; }
    int getRemainingTime() const { return remainingTime; }
    int getExecutedTime() const { return executedTime; }
    
    // Setters
    void setState(ProcessState s) { state = s; }
    void setStartTime(int time);
    void setFinishTime(int time);
    void setWaitingTime(int time) { waitingTime = time; }
    void setTurnaroundTime(int time) { turnaroundTime = time; }
    void setResponseTime(int time) { responseTime = time; }
    void setRemainingTime(int time) { remainingTime = time; }
    void setExecutedTime(int time) { executedTime = time; }
    
    // Métodos de utilidad
    void calculateMetrics();
    std::string getStateString() const;
    
    // Operadores para comparación
    bool operator<(const Process& other) const;
};

#endif // PROCESS_H

