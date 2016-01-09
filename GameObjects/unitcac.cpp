#include "unitcac.h"



UnitCaC::UnitCaC(char _type, bool _isJoueurUniteS,SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer):
Unit(_type,_isJoueurUniteS,texture,positionTexture,positionCarte,renderer)
{
    attackTimer = 0;
    attackCD = 100;
    range = 20;
    damage = 20;
}
UnitCaC::~UnitCaC()
{
    //dtor
}

void UnitCaC::UnitMove(int _x, int _y)
{
    if (path.empty()){
        Tools::Astar(Tools::GetNodeFromAxis(x,y),Tools::GetNodeFromAxis(_x,_y),pathingMap, path);
    }
    else{
        int index;
        index = path.size()-1;
        Node currentNode = path[index];
        Vector2D target = Vector2D(currentNode.GetWorldX(),currentNode.GetWorldY());
        Vector2D steering = (facing.Normalized() * speed) + (Seek(target)*pathForce);
        Move(steering);
        if(Tools::DistanceEuclidienne(x,target.x,y,target.y) <= (40/2)){
            path.erase(path.begin()+index);
        }
    }
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