#ifndef TASK_H
#define TASK_H

#include "unit.h"

class Task
{
    public:
        Task();
        virtual ~Task();
        virtual bool execute(Unit &unit);
        virtual bool exitCondition(Unit unit);
    protected:
    private:
};

#endif // TASK_H
