#include "task.h"

Task::Task(std::string _name)
{
    name = name;
}

Task::~Task()
{
    //dtor
}

bool Task::execute(Unit &unit)
{
    unit.SetDestination(200,200);
}

bool Task::exitCondition(Unit unit)
{
    //exitCondition
}
