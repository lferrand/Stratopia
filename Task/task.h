#ifndef TASK_H
#define TASK_H

#include "unit.h"

class Task
{
    public:
        Task(std::string name);
        virtual ~Task();
        virtual bool execute(Unit &unit);
        virtual bool exitCondition(Unit unit);
    protected:
        std::string name;
    private:
};

#endif // TASK_H
