#include "process.h"
#include <algorithm>

Process::Process(int id, int arrivalTime, int burstTime, int priority)
    : id(id), arrivalTime(arrivalTime), burstTime(burstTime), priority(priority),
      state(ProcessState::NEW), startTime(-1), finishTime(-1),
      waitingTime(0), turnaroundTime(0), responseTime(0),
      remainingTime(burstTime), executedTime(0) {
}

void Process::setStartTime(int time) {
    if (startTime == -1) {
        startTime = time;
        responseTime = startTime - arrivalTime;
    }
}

void Process::setFinishTime(int time) {
    finishTime = time;
    turnaroundTime = finishTime - arrivalTime;
    waitingTime = turnaroundTime - burstTime;
}

void Process::calculateMetrics() {
    if (finishTime != -1) {
        turnaroundTime = finishTime - arrivalTime;
        waitingTime = turnaroundTime - burstTime;
    }
    if (startTime != -1 && responseTime == 0) {
        responseTime = startTime - arrivalTime;
    }
}

std::string Process::getStateString() const {
    switch(state) {
        case ProcessState::NEW: return "Nuevo";
        case ProcessState::READY: return "Listo";
        case ProcessState::RUNNING: return "Ejecutando";
        case ProcessState::TERMINATED: return "Terminado";
        default: return "Desconocido";
    }
}

bool Process::operator<(const Process& other) const {
    return arrivalTime < other.arrivalTime;
}

