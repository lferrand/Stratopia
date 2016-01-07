#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
    private:
        int id;
        float x;
        float y;

    public:
        GameObject();
        virtual ~GameObject();
        float getX();
        float getY();
        void setX(int x);
        void setY(int y);
        int getId();
    protected:


};

#endif // GAMEOBJECT_H
