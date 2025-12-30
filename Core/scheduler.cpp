#include "scheduler.h"

Scheduler::Scheduler() : currentTime(0) {
}

void Scheduler::addProcess(const Process& process) {
    processes.push_back(process);
    originalProcesses.push_back(process);
}

void Scheduler::addProcesses(const std::vector<Process>& processes) {
    for (const auto& p : processes) {
        this->processes.push_back(p);
        originalProcesses.push_back(p);
    }
}

void Scheduler::clearProcesses() {
    processes.clear();
    originalProcesses.clear();
    ganttChart.clear();
    currentTime = 0;
}

void Scheduler::reset() {
    processes = originalProcesses;
    for (auto& p : processes) {
        p.setState(ProcessState::NEW);
        p.setStartTime(-1);
        p.setFinishTime(-1);
        p.setWaitingTime(0);
        p.setTurnaroundTime(0);
        p.setResponseTime(0);
        p.setRemainingTime(p.getBurstTime());
        p.setExecutedTime(0);
    }
    ganttChart.clear();
    currentTime = 0;
}

void Scheduler::executeProcess(Process& process, int startTime, int duration) {
    process.setState(ProcessState::RUNNING);
    process.setStartTime(startTime);
    
    int actualDuration = std::min(duration, process.getRemainingTime());
    process.setExecutedTime(process.getExecutedTime() + actualDuration);
    process.setRemainingTime(process.getRemainingTime() - actualDuration);
    
    addToGanttChart(process.getId(), actualDuration);
    currentTime += actualDuration;
    
    if (process.getRemainingTime() == 0) {
        process.setState(ProcessState::TERMINATED);
        process.setFinishTime(currentTime);
        process.calculateMetrics();
    } else {
        process.setState(ProcessState::READY);
    }
}

void Scheduler::addToGanttChart(int processId, int time) {
    ganttChart.push_back({processId, time});
}

