#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "controller.h"
#include "task.h"


class AIController : public Controller
{
    public:
        AIController(std::vector<Task*> &_FSM):FSM(_FSM)
        {
            std::cout << FSM.size();
            currentTask = 0;
        }
        virtual ~AIController();
        virtual bool Reflex(Unit &unit);
        virtual void Update(Unit &unit);
        std::vector<Task*> &FSM;
    protected:
        int currentTask;

    private:
};

#endif // AICONTROLLER_H
