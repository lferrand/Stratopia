#ifndef ATTACK_H
#define ATTACK_H

#include "Task.h"


class Attack : public Task
{
    public:
        Attack(std::string name);
        virtual ~Attack();
        virtual bool execute(Unit &unit);
        virtual bool exitCondition(Unit &unit);
    protected:
    private:
};

#endif // ATTACK_H
