#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include <movableobject.h>


class RenderableObject : public MovableObject
{
    public:
        RenderableObject();
        virtual ~RenderableObject();
        void setHealth();
        float getHealth();
    protected:
    private:
        float health;
};

#endif // RENDERABLEOBJECT_H
