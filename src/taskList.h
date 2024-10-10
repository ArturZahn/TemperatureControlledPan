#ifndef TASKLIST_H
#define TASKLIST_H

#include <vector>
#include <memory>

#include "print.h"
#include "task.h"

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

class taskList
{
private:
    int currentTask;
    void startNextTask();
    bool isRunning;
    bool finished;
public:
    std::vector<std::unique_ptr<task>> tasks;
    taskList();
    void runAll();
    int getCurrentTask();
    void handle();
    bool checkIfIsRunning();
    bool checkIfFinished();
};


#endif