#ifndef PRIORITY_H
#define PRIORITY_H

#include "../Core/scheduler.h"

class PriorityScheduler : public Scheduler {
private:
    bool preemptive;  // true = con desalojo, false = sin desalojo
    
public:
    PriorityScheduler(bool preemptive = false);
    void schedule() override;
    std::string getName() const override { 
        return std::string(preemptive ? "Prioridades (Con Desalojo)" : "Prioridades (Sin Desalojo)"); 
    }
    void setPreemptive(bool p) { preemptive = p; }
    bool isPreemptive() const { return preemptive; }
    
private:
    Process* getHighestPriorityProcess(int currentTime);
};

#endif // PRIORITY_H

