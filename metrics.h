#ifndef METRICS_H
#define METRICS_H

#include "Core/process.h"
#include <vector>
#include <string>
#include <map>

struct SystemMetrics {
    double averageTurnaroundTime;
    double averageWaitingTime;
    double averageResponseTime;
    double cpuUtilization;
    
    SystemMetrics() : averageTurnaroundTime(0), averageWaitingTime(0), 
                     averageResponseTime(0), cpuUtilization(0) {}
};

class MetricsCalculator {
public:
    static SystemMetrics calculateSystemMetrics(const std::vector<Process>& processes, int totalTime);
    static void printProcessMetrics(const std::vector<Process>& processes);
    static void printSystemMetrics(const SystemMetrics& metrics);
    static void printGanttChart(const std::vector<std::pair<int, int>>& ganttChart);
    static std::map<std::string, SystemMetrics> compareAlgorithms(
        const std::map<std::string, std::vector<Process>>& results,
        const std::map<std::string, int>& totalTimes);
};

#endif // METRICS_H

