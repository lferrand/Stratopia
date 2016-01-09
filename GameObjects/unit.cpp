#include "unit.h"
#include "vector2d.h"




Unit::~Unit()
{
    //dtor
}

void Unit::UnitMove(int x, int y)
{
    //something
}

Vector2D Unit::Seek(Vector2D target){
    Vector2D currentPosition = Vector2D(x,y);
    Vector2D directionTo = target - currentPosition;
    return directionTo.Normalized();
}

void Unit::Move(Vector2D movement)
{
    x = x + (int)movement.x;
    y = y + (int)movement.y;
}

void Unit::Attack(Unit& target)
{
    //someting
}

bool Unit::Die()
{
    //something
}
