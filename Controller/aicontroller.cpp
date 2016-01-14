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
    if(unit.getHealth()<=50 && unit.CanRunAway() && (unit.GetTarget() != NULL && unit.GetType() == 'c' && unit.GetTarget()->GetType() != 'd')){

        unit.runAwayTimer++;
        unit.SetNullTarget();
        unit.RunAway();

        return true;
    }
    return false;
}
bool AIController::ProcessMessage(Unit &unit)
{
    std::vector<Message> messagesReceived = unit.GetMessages();
    if(!messagesReceived.empty() && unit.GetTarget()== NULL){

        float currentLenght = 0;
        float bestLenght = (messagesReceived[0].sender->GetPosition() - unit.GetPosition()).Length();
        Message closestMessage = messagesReceived[0];
        for(std::vector<Message>::iterator it = messagesReceived.begin(); it != messagesReceived.end(); ++it) {
                Message currentObject = *it;
                currentLenght = (currentObject.sender->GetPosition() - unit.GetPosition()).Length();
                if (currentLenght < bestLenght){
                    closestMessage = currentObject;
                    bestLenght = currentLenght;
                }
        }
        if(!closestMessage.content.compare("attack") && bestLenght < 400){
            unit.SetTarget(closestMessage.target);
            unit.SetNullDestination();
            unit.ClearMessages();
            return true;
        }
    }
    unit.ClearMessages();
    return false;

}

void AIController::Update(Unit &unit)
{
    if(!ProcessMessage(unit)){
        if(!Reflex(unit)){

            if(FSM[currentTask]->execute(unit)){
                currentTask++;
                if (currentTask >= FSM.size()){
                    currentTask = 0;
                }
            }
        }
    }

}
