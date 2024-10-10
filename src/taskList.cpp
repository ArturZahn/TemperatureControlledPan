#include "taskList.h"


taskList::taskList()
{
    this->currentTask = -1;
    this->isRunning = false;
    this->finished = false;
}
int taskList::getCurrentTask()
{
    return this->currentTask;
}
bool taskList::checkIfIsRunning()
{
    return this->isRunning;
}
bool taskList::checkIfFinished()
{
    return this->finished;
}
void taskList::runAll()
{
    if(this->tasks.size() > 0)
    {
        this->isRunning = true;
        this->currentTask = -1;
        this->startNextTask();
    }
}
void taskList::startNextTask()
{
    this->currentTask++;
    if(this->currentTask >= this->tasks.size())
    {
        // ended all tasks
        myprintln("Acabou");
        this->currentTask = -1;
        this->isRunning = false;
        this->finished = true;
    }
    else
    {
        this->tasks[this->currentTask]->start();
        myprintln("Tarefa ");
        myprintln(this->currentTask);
        myprintln(" iniciada");
    }
}

void taskList::handle()
{
    if(this->isRunning)
    {
        this->tasks[this->currentTask]->handle();

        if(this->tasks[this->currentTask]->checkIfFinished())
            this->startNextTask();
    }
}