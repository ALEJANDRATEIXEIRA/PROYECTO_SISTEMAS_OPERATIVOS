#ifndef SJF_H
#define SJF_H

#include "../Core/scheduler.h"

class SJF : public Scheduler {
public:
    SJF();
    void schedule() override;
    std::string getName() const override { return "SJF (Shortest Job First)"; }
    
private:
    Process* getShortestJob(int currentTime);
};

#endif // SJF_H

