#ifndef FCFS_H
#define FCFS_H

#include "../Core/scheduler.h"

class FCFS : public Scheduler {
public:
    FCFS();
    void schedule() override;
    std::string getName() const override { return "FCFS (First Come First Served)"; }
};

#endif // FCFS_H




