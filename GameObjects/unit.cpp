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
        ChangerSpriteDirection();
        AnimationSprite();

    }
    else if(destination != NULL){
        this->UnitMove();
        ChangerSpriteDirection();
        AnimationSprite();
    }
    else{
    }
}
void Unit::AnimationSprite()
{
    etapeAnimation++;
    int vitesseAnimation=6;
    if(etapeAnimation<vitesseAnimation)
    {
        numeroSpriteAAfficher[1]=2;
    }
    else if(etapeAnimation<vitesseAnimation*2)
    {
        numeroSpriteAAfficher[1]=1;
    }
    else if(etapeAnimation<vitesseAnimation*3)
    {
        numeroSpriteAAfficher[1]=2;
    }
    else if(etapeAnimation<vitesseAnimation*4)
    {
        numeroSpriteAAfficher[1]=0;
    }
    else if(etapeAnimation<vitesseAnimation*5)
    {
        numeroSpriteAAfficher[1]=4;
    }
    else if(etapeAnimation<vitesseAnimation*6)
    {
        numeroSpriteAAfficher[1]=3;
    }
    else if(etapeAnimation<vitesseAnimation*7)
    {
        numeroSpriteAAfficher[1]=4;
    }
    else if(etapeAnimation<vitesseAnimation*8)
    {
        numeroSpriteAAfficher[1]=0;
    }
    else
    {
        etapeAnimation=0;
    }

}


std::vector<RenderableObject*> Unit::GetPercept()
{
    std::vector<RenderableObject*> renderableInVision;
    for(std::vector<RenderableObject*>::iterator it = objects.begin(); it != objects.end(); ++it) {
            RenderableObject* currentObject = *it;
//            std::cout << " distance " <<(pow(currentObject->getX()- x,2) + pow(currentObject->getY()- y,2))<< "\n";
//            std::cout << " vision " << pow(vision,2) << "\n";

            if ((pow(currentObject->getX()- x,2) + pow(currentObject->getY()- y,2)) <= pow(vision,2)){
                renderableInVision.push_back(currentObject);
            }
    }
//    std::cout << "tout object " <<objects.size()<< "\n";
//    std::cout << "renduVision " <<renderableInVision.size()<< "\n";
    return renderableInVision;
}

void Unit::UnitMove()
{
}

void Unit::ChangerSpriteDirection()
{
    switch(GetDirection())
    {
    case N:
        numeroSpriteAAfficher[0]=0;
        symetrieSpriteNecessaire=false;
        break;
    case S:
        numeroSpriteAAfficher[0]=4;
        symetrieSpriteNecessaire=false;
        break;
    case E:
        numeroSpriteAAfficher[0]=2;
        symetrieSpriteNecessaire=false;
        break;
    case SE:
        numeroSpriteAAfficher[0]=3;
        symetrieSpriteNecessaire=false;
        break;
    case NE:
        numeroSpriteAAfficher[0]=1;
        symetrieSpriteNecessaire=false;
        break;
    case W:
        numeroSpriteAAfficher[0]=2;
        symetrieSpriteNecessaire=true;
        break;
    case SW:
        numeroSpriteAAfficher[0]=3;
        symetrieSpriteNecessaire=true;
        break;
    case NW:
        numeroSpriteAAfficher[0]=1;
        symetrieSpriteNecessaire=true;
        break;


    }
}

int Unit::GetDirection()
{
    float sensibiliteFacing(0.5);
    if(facing.x >= sensibiliteFacing)
    {
        if(facing.y>=sensibiliteFacing)
        {
            return SE;
        }
        else if(facing.y<-sensibiliteFacing)
        {
            return NE;
        }
        else return E;
    }
    else if(facing.x <-sensibiliteFacing)
    {
        if(facing.y>=sensibiliteFacing)
        {
            return SW;
        }
        else if(facing.y<-sensibiliteFacing)
        {
            return NW;
        }
        else return W;
    }
    else
    {
        if(facing.y>=sensibiliteFacing)
        {
            return S;
        }
        else if(facing.y<-sensibiliteFacing)
        {
            return N;
        }
            return S;

    }

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
