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
//    if(unit.GetType() == 'c'){
//        return exitCondition(unit);
//    }
//    else{
//        if (unit.CanAttack()){
//            unit.SetNullDestination();
//            RenderableObject* newTarget = unit.GetClosestEnemy();
//            unit.SetTarget(newTarget);
//        }
//        else{
//            unit.SetNullTarget();
//            unit.RunAway();
//        }
//        return exitCondition(unit);
//
//    }
    RenderableObject* enemy = unit.GetClosestEnemy();
    if(enemy != NULL && enemy != unit.GetTarget()){
        Message attackMessage = Message("attack",&unit,enemy);
        unit.SendMessageAllAlly(attackMessage);
        unit.SetTarget(enemy);
    }
    return exitCondition(unit);
    //unit.ClearPath();
}

bool Attack::exitCondition(Unit &unit)
{
    if(unit.GetTarget() == NULL && unit.GetClosestEnemy() == NULL){
        return true;
    }
    if(unit.GetTarget() != NULL && unit.GetTarget()->IsDead()){
        unit.SetNullTarget();
        unit.SetNullDestination();
        return true;
    }
    return false;
}
