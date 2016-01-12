#include "unitdistance.h"
#include "tools.h"
#include "math.h"

UnitDistance::UnitDistance(char _type, bool _isJoueurUniteS, SDL_Rect positionCarte,SDL_Renderer *renderer,bool** pathMap,UnitTextures &texts,std::vector<RenderableObject*> &_objects,int _playerID):
Unit(_type,_isJoueurUniteS,positionCarte,renderer,pathMap,texts,_objects,_playerID)
{
    vision = 100;
    attackTimer = 0;
    attackCD = 100;
    range = 100;
    damage = 20;
    facing = Vector2D(5,10);
    target = NULL;
    destination = NULL;
    AIcontroller = NULL;
}

UnitDistance::~UnitDistance()
{
    //dtor
}

void UnitDistance::UnitMove()
{
    if (destination->x == x && destination->y == y){
        delete destination;
        destination = NULL;
    }
    if (destination != NULL){

        Node destinationNode = Tools::GetNodeFromAxis(static_cast <int> (floor(destination->x)),floor(destination->y));
        //std::cout << "out of bound X :"<< (int) destinationNode.GetX() << "out of bound Y :"<< (int) destinationNode.GetX() <<"\n" ;
        if (!Tools::CheckInBound(destinationNode)){
            if (destinationNode.GetX()<0){
                destinationNode.SetX(0);
            }
            if (destinationNode.GetY()<0){
                destinationNode.SetY(0);
            }
            if (destinationNode.GetX()>33){
                destinationNode.SetX(33);
            }
            if (destinationNode.GetY()>33){
                destinationNode.SetY(33);
            }
            delete destination;
            destination = new Vector2D(destinationNode.GetWorldX(),destinationNode.GetWorldY());
        }
        if ( !Tools::Passable(destinationNode,pathingMap)){

            destinationNode = Tools::FindClosestPassable(Tools::GetNodeFromAxis(x,y),destinationNode,pathingMap);
            //std::cout << "position x : \n";
            delete destination;
            destination = new Vector2D(destinationNode.GetWorldX(),destinationNode.GetWorldY());
        }


        if (path.empty()){
            Tools::Astar(Tools::GetNodeFromAxis(x,y),destinationNode,pathingMap, path);
        }
        else{
            //std::cout << "position x : " << x << "position y : " << y << "\n";
            Vector2D targetPosition;
            int index = 0;
            index = path.size()-1;
            speed = 1.5;
            pathForce = 1;
            Node currentNode = path[index];
            //std::cout << "node x : " << currentNode.GetWorldX() << "node y : " << currentNode.GetWorldY() << "\n";
            if (path.size() == 1){
                targetPosition = Vector2D(destination->x,destination->y);
            }
            else{
                targetPosition = Vector2D(currentNode.GetWorldX(),currentNode.GetWorldY());
            }

            //std::cout << "seek x : " << Seek(targetPosition).x << "seek y : " << Seek(targetPosition).y << "\n";
            Vector2D steering = velocity + Seek(targetPosition).Normalized() + AvoidUnitCollision();
            facing = steering.Normalized();
            velocity = steering;
            velocity.Truncate(speed);
            //std::cout << "steering x : " << steering.x << "steering y : " << steering.y << "\n";
            Move(steering);


            if( Seek(targetPosition).Length()<= (32/2) && path.size() !=1){
                path.erase(path.begin()+index);
            }else if (Seek(targetPosition).Length() <= 0 && path.size() == 1){
                delete destination;
                destination = NULL;
                //std::cout << Seek(targetPosition).Length()<< "\n";
                path.erase(path.begin()+index);
            }

            if (destinationNode.GetX() != path[0].GetX() || destinationNode.GetY()!= path[0].GetY()){
                //std::cout << "clear" << "\n";
                path.clear();
            }
            //std::cout << Seek(targetPosition).Length()<< "\n";
        }
    }
    else{
        path.clear();
    }
}

void UnitDistance::Update()
{
    if(AIcontroller != NULL){
        AIcontroller->Update(*this);
    }
    Unit::Update();
}

bool UnitDistance::Attack()
{
     if(target != NULL){

        float distance = (Vector2D(x,y) - Vector2D(target->getX(),target->getY())).Length();
        if(distance <= range){
                attaqueEnCours=true;
        }
        if(attaqueEnCours)
        {
            if(attackTimer < attackCD){
            attackTimer++;
            return true;
            }
            else
            {
                target->setHealth(target->getHealth() - this->damage);
                this->attackTimer = 0;
                attaqueEnCours=false;
                return true;
            }
        }
        else{
            delete destination;
            destination = new Vector2D(target->getX(),target->getY());
            UnitMove();
            return false;
        }
    }
    return false;

}
void UnitDistance::AnimationSpriteCombat()
{
    int vitesseAnimation=attackCD/4;
    if(attackTimer<vitesseAnimation)
    {
        numeroSpriteAAfficher[1]=4;
    }
    else if(attackTimer<vitesseAnimation*2)
    {
        numeroSpriteAAfficher[1]=5;
    }
    else if(attackTimer<vitesseAnimation*3)
    {
        numeroSpriteAAfficher[1]=6;
    }
    else if(attackTimer<vitesseAnimation*5)
    {
        numeroSpriteAAfficher[1]=0;
    }

}
bool UnitDistance::Die()
{
    if(health <= 0){
        delete this;
        return true;
    }
    return false;
}
