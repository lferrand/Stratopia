#include "aicontroller.h"






AIController::~AIController()
{
    //dtor
}

bool AIController::Reflex(Unit &unit)
{
    if(unit.getHealth()<=50){
        unit.SetDestination(300,50);
        return true;
    }
    return false;
}

void AIController::Update(Unit &unit)
{
    if(!Reflex(unit)){
        std::cout << FSM.size();
        if(FSM[currentTask]->execute(unit)){
            currentTask++;
            std::cout << "test";
            if (currentTask >= FSM.size()){
                currentTask = 0;
            }
        }
    }
}
