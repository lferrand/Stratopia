#include "Explore.h"
#include "math.h"

Explore::Explore(std::string _name):Task(_name)
{
}

Explore::~Explore()
{
    //dtor
}

bool Explore::execute(Unit &unit)
{
    Vector2D newDestitation;
    Vector2D position = Vector2D(unit.getX(),unit.getY());

    float randomAngle = rand() % 90 - 45;

    Vector2D test = unit.GetFacing();
    newDestitation = position + (unit.GetFacing().RotateByAngle(randomAngle)*40);

    //std::cout << "position x : y " << position.x << " " << position.y << "\n";
    //std::cout << "new destination x : y " << newDestitation.x << " " << newDestitation.y << "\n";
    if (unit.GetDestination()!= NULL){
        Vector2D destination = *unit.GetDestination();
        if ((destination - position).Length() > 2){
            return exitCondition(unit);
        }
    }

    unit.SetDestination(newDestitation.x,newDestitation.y);
    return false;
    //unit.ClearPath();
}

bool Explore::exitCondition(Unit &unit)
{
    std::vector<RenderableObject*> objectInVision = unit.GetPercept();
    std::vector<RenderableObject*> enemyInVision;

    for(std::vector<RenderableObject*>::iterator it = objectInVision.begin(); it != objectInVision.end(); ++it) {
            RenderableObject* currentObject = *it;
            if (currentObject->GetPlayerID() != unit.GetPlayerID()){
                enemyInVision.push_back(currentObject);
            }
    }
    std::cout << "object " <<objectInVision.size()<< "\n";
    std::cout << "enemy " <<enemyInVision.size()<< "\n";

    if(!enemyInVision.empty()){

        RenderableObject* closesestUnit = enemyInVision[0];
        for(std::vector<RenderableObject*>::iterator it = objectInVision.begin(); it != objectInVision.end(); ++it) {
            RenderableObject* currentObject = *it;
            if (pow(currentObject->getX()- unit.getX(),2) + pow(currentObject->getY()- unit.getY(),2) <= pow(closesestUnit->getX()- unit.getX(),2) + pow(closesestUnit->getY()- unit.getY(),2)){
                closesestUnit = currentObject;
            }
        }
        unit.SetTarget(closesestUnit);
        return true;
    }
    return false;
}
