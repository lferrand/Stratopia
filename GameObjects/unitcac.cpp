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

void UnitCaC::UnitMove()
{
    if (destination->x == x && destination->y == y){
        delete destination;
        destination = NULL;
    }
    if (destination != NULL){
        if (path.empty()){
        Tools::Astar(Tools::GetNodeFromAxis(x,y),Tools::GetNodeFromAxis(destination->x,destination->y),pathingMap, path);
        }
        else{
            //std::cout << "position x : " << x << "position y : " << y << "\n";
            Vector2D target;
            int index = 0;
            index = path.size()-1;
            speed = 1;
            pathForce = 1;
            Node currentNode = path[index];
            //std::cout << "node x : " << currentNode.GetWorldX() << "node y : " << currentNode.GetWorldY() << "\n";
            if (path.size() == 1){
                target = Vector2D(destination->x,destination->y);
            }
            else{
                target = Vector2D(currentNode.GetWorldX(),currentNode.GetWorldY());
            }

            //std::cout << "seek x : " << Seek(target).x << "seek y : " << Seek(target).y << "\n";
            Vector2D steering = velocity + Seek(target).Normalized();
            facing = velocity.Normalized();
            velocity = steering;
            velocity.Truncate(speed);
            //std::cout << "steering x : " << steering.x << "steering y : " << steering.y << "\n";
            Move(steering);
            //std::cout << Seek(target).Length()<< "\n";
            if( Seek(target).Length()<= (20/2) && path.size() !=1){
                path.erase(path.begin()+index);
            }else if (Seek(target).Length() <= 0 && path.size() == 1){
                delete destination;
                destination = NULL;
                std::cout << Seek(target).Length()<< "\n";
                path.erase(path.begin()+index);
            }
        }
    }
    else{
        path.clear();
    }

}

void UnitCaC::Attack(Unit& target)
{
    if(Tools::DistanceEuclidienne(this->getX(),target.getX(),this->getY(),target.getY())<= range){
        target.setHealth(target.getHealth() - this->damage);
        this->attackTimer = 0;
    }
    else{
        delete destination;
        destination = new Vector2D(target.getX(),target.getY());
        UnitMove();
    }
}

bool UnitCaC::Die()
{
    if(health <= 0){
        delete this;
    }
}
