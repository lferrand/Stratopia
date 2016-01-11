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
    delete destination;
    destination = new Vector2D(_x,_y);
}
void Unit::SetTarget(Unit* &_target)
{
    target = _target;
}
void Unit::SetTarget(RenderableObject* &_target)
{
    target = _target;
}
Vector2D Unit::GetFacing()
{
    return facing;
}
Vector2D* Unit::GetDestination()
{
    return destination;
}

Vector2D Unit::GetVelocity()
{
    return velocity;
}
void Unit::ClearPath()
{
    path.clear();
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

std::vector<RenderableObject*> Unit::GetPercept()
{
    std::vector<RenderableObject*> renderableInVision;
    for(std::vector<RenderableObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            RenderableObject* currentObject = *it;
            std::cout << " distance " <<(pow(currentObject->getX()- x,2) + pow(currentObject->getY()- y,2))<< "\n";
            std::cout << " vision " << pow(vision,2) << "\n";

            if ((pow(currentObject->getX()- x,2) + pow(currentObject->getY()- y,2)) <= pow(vision,2)){
                renderableInVision.push_back(currentObject);
            }
    }
    std::cout << "tout object " <<objects.size()<< "\n";
    std::cout << "renduVision " <<renderableInVision.size()<< "\n";
    return renderableInVision;
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
