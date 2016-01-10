#include "unit.h"
#include "tools.h"
#include "vector2d.h"
#include "math.h"
#include "aicontroller.h"




Unit::~Unit()
{
    //dtor
}
void Unit::SetPathingMap(bool** &pathingMap)
{
    this->pathingMap = pathingMap;
}

void Unit::SetFacing(Vector2D face)
{
    facing = face.Normalized();

}
void Unit::SetDestination(int _x, int _y)
{
    destination = new Vector2D(_x,_y);
}
void Unit::SetTarget(Unit* &_target)
{
    target = _target;
}

void Unit::Update()
{
    if(target != NULL){
        //std::cout << "attack";
        this->Attack();
    }
    else if(destination != NULL){
        this->UnitMove();
    }
    else{
        //std::cout << "idle";
    }
}

void Unit::UnitMove()
{
    //someting
}

Vector2D Unit::Seek(Vector2D target){
    Vector2D currentPosition = Vector2D(x,y);
    Vector2D directionTo = target - currentPosition;
    //std::cout << "directionTo x : " << directionTo.x << "directionTo y : " << directionTo.y << "\n";
    return directionTo;
}

void Unit::Move(Vector2D movement)
{
    x = x + floor(movement.x + 0.5);
    y = y + floor(movement.y + 0.5);
}

void Unit::Attack()
{
    //someting
}

bool Unit::Die()
{
    //something
}
