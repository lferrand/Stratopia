#include "Explore.h"
#include "math.h"
#include <time.h>

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

    srand(time(0));
    float randomAngle = rand() % 90 - 45;

    Vector2D test = unit.GetFacing();
    newDestitation = position + (unit.GetFacing().RotateByAngle(randomAngle)*100);

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
        RenderableObject* closesestUnit = unit.GetClosestEnemy();

        if (closesestUnit != NULL){
            unit.SetTarget(closesestUnit);
            return true;
        }

        return false;
}
