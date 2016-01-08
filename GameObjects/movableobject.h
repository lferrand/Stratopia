#ifndef MOVABLEOBJECT_H
#define MOVABLEOBJECT_H

#include "gameobject.h"


class MovableObject : public GameObject
{
    public:
        MovableObject();
        MovableObject(int x, int y):GameObject(x,y){}
        virtual ~MovableObject();
        int Getspeed() { return speed; }
        void Setspeed(int val) { speed = val; }
    protected:
    private:
        int speed;
};

#endif // MOVABLEOBJECT_H
