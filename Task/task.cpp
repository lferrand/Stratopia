#include "task.h"

Task::Task()
{
    //ctor
}

Task::~Task()
{
    //dtor
}

bool Task::execute(Unit &unit)
{
    std::cout << "test";
    unit.SetDestination(50,50);
}

bool Task::exitCondition(Unit unit)
{
    //exitCondition
}
