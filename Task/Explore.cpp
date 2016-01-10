#include "Explore.h"

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
    std::cout << "random angle " << randomAngle << "\n";
    Vector2D test = unit.GetFacing();
    test = test * 10;
    std::cout << "test x : y " << test.x << " " << test.y << "\n";
    std::cout << "facing x : y " << unit.GetFacing().x * 10 << " " << unit.GetFacing().y * 10 << "\n";

    newDestitation = position + (unit.GetFacing().RotateByAngle(randomAngle)*40);
    std::cout << "position x : y " << position.x << " " << position.y << "\n";
    std::cout << "new destination x : y " << newDestitation.x << " " << newDestitation.y << "\n";
    if (unit.GetDestination()!= NULL){
        Vector2D destination = *unit.GetDestination();
        std::cout << "length" <<(destination - position).Length()<< "\n";
        if ((destination - position).Length() > 2){
            return false;
        }
    }

    unit.SetDestination(newDestitation.x,newDestitation.y);
    return false;
    //unit.ClearPath();
}

bool Explore::exitCondition(Unit unit)
{
    //exitCondition
}
