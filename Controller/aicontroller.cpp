#include "aicontroller.h"


AIController::AIController(std::vector<Task*> &_FSM):
    FSM(_FSM)
{

    FSM = _FSM;
    currentTask = 0;
}

AIController::~AIController()
{
    //dtor
}

bool AIController::Reflex(Unit &unit)
{
    if(unit.getHealth()<=50 && unit.CanRunAway()){
        unit.runAwayTimer++;
        unit.SetNullTarget();
        unit.RunAway();
        return true;
    }
    else{
        unit.runAwayTimer = 0;
    }
    return false;
}

void AIController::Update(Unit &unit)
{
    if(!Reflex(unit)){

        if(FSM[currentTask]->execute(unit)){
            currentTask++;
            if (currentTask >= FSM.size()){
                currentTask = 0;
            }
        }
    }
}
