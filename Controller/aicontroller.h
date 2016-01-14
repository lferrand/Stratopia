#ifndef AICONTROLLER_H
#define AICONTROLLER_H

#include "controller.h"
#include "task.h"


class AIController : public Controller
{
    public:
        AIController(std::vector<Task*>& _FSM);
        virtual ~AIController();
        virtual bool Reflex(Unit &unit);
        virtual void Update(Unit &unit);
        virtual bool ProcessMessage(Unit &unit);

    protected:
        std::vector<Task*> &FSM;
        int currentTask;

    private:
};

#endif // AICONTROLLER_H
