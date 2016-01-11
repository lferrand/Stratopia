#include "attack.h"

Attack::Attack( std::string _name):Task(_name)
{
    //ctor
}

Attack::~Attack()
{
    //dtor
}

bool Attack::execute(Unit &unit)
{

    return exitCondition(unit);
    //unit.ClearPath();
}

bool Attack::exitCondition(Unit &unit)
{
    if(unit.GetTarget()->IsDead()){
        unit.SetNullTarget();
        unit.SetNullDestination();
        return true;
    }
    return false;
}
