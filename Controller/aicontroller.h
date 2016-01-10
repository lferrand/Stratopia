#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "controller.h"
#include "unit.h"
#include "task.h"


class AIController : public Controller
{
    public:
        AIController();
        AIController(std::vector<Task*> &_FSM);
        virtual ~AIController();
        virtual bool Reflex(Unit &unit);
        virtual void Update(Unit &unit);
        std::vector<Task*> &FSM;
    protected:
        int currentTask;

    private:
};

#endif // AICONTROLLER_H
