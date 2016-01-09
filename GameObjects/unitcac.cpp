#include "unitcac.h"
#include "tools.h"

UnitCaC::UnitCaC(float _attackTimer, float _attackCD , int _range, int _damage, char _type, bool _isJoueurUnite)
{
    attackTimer = _attackTimer;
    attackCD = _attackCD;
    range = _range;
    damage = _damage;
    type = _type;
    isJoueurUnite = _isJoueurUnite;
}

UnitCaC::~UnitCaC()
{
    //dtor
}

void UnitCaC::UnitMove(int x, int y)
{

}

void UnitCaC::Attack(Unit& target)
{
    if(Tools::DistanceEuclidienne(this->getX(),target.getX(),this->getY(),target.getY())<= range){
        target.setHealth(target.getHealth() - this->damage);
        this->attackTimer = 0;
    }
    else{
        UnitMove(target.getX(),target.getY());
    }
}

bool UnitCaC::Die()
{
    if(health <= 0){
        delete this;
    }
}
