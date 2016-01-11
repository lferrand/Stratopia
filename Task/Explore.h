#ifndef EXPLORE_H
#define EXPLORE_H

#include "task.h"


class Explore : public Task
{
    public:
        Explore(std::string name);
        virtual ~Explore();
        virtual bool execute(Unit &unit);
        virtual bool exitCondition(Unit &unit);
    protected:
    private:
};

#endif // EXPLORE_H
