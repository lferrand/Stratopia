#include "unitdistance.h"
#include "tools.h"

UnitDistance::UnitDistance()
{
    //ctor
}

UnitDistance::~UnitDistance()
{
    //dtor
}

void UnitDistance::UnitMove(int x, int y)
{

}

void UnitDistance::Attack(Unit& target)
{
    if(Tools::DistanceEuclidienne(this->x,target.getX(),this->y,target.getY())<= this->range){
        target.setHealth(target.getHealth() - this->damage);
        this->attackTimer = 0;
    }
    else{
        UnitMove(target.getX(),target.getY());
    }
}

bool UnitDistance::Die()
{
    if(health <= 0){
        delete this;
    }
}
