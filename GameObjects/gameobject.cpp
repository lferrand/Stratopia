#include "gameobject.h"

GameObject::GameObject()
{
    x = 100;
    y = 0;
}

GameObject::~GameObject()
{
    x = 0;
    y = 0;
}

int GameObject::getId()
{
    return id;
}

int GameObject::getX()
{
    return x;
}

int GameObject::getY()
{
    return y;
}

Vector2D GameObject::GetPosition()
{
    Vector2D position = Vector2D(x,y);
    return position;
}

void GameObject::setX(int x){
  this->x = x;
}
void GameObject::setY(int y){
   this->y = y;
}
