#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "gameobject.h"


class MovableObject : public GameObject
{
    public:
        MovableObject(int x, int y):GameObject(x,y){}
        virtual ~MovableObject();
        int Getspeed() { return speed; }
        void Setspeed(int val) { speed = val; }
    protected:
        int speed;
        int pathForce;
    private:

};

#endif // MOVABLEOBJECT_H
