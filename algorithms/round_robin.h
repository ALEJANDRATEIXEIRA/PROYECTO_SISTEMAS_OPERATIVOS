#ifndef ROUND_ROBIN_H
#define ROUND_ROBIN_H

#include "../Core/scheduler.h"

class RoundRobin : public Scheduler {
private:
    int quantum;
    
public:
    RoundRobin(int quantum = 4);
    void schedule() override;
    std::string getName() const override { return "Round Robin (Quantum: " + std::to_string(quantum) + ")"; }
    void setQuantum(int q) { quantum = q; }
    int getQuantum() const { return quantum; }
};

#endif // ROUND_ROBIN_H

