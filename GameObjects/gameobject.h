#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>>

class GameObject
{
    private:
        int id;


    public:
        GameObject();
        GameObject(int x1, int y1):x(x1),y(y1){}
        virtual ~GameObject();
        int getX();
        int getY();
        void setX(int x);
        void setY(int y);
        int getId();
    protected:
        int x;
        int y;
};

#endif // GAMEOBJECT_H
