#include "unit.h"
#include "tools.h"
#include "vector2d.h"
#include "math.h"




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

void Unit::UnitMove()
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

void Unit::Attack(Unit& target)
{
    //someting
}

bool Unit::Die()
{
    //something
}
