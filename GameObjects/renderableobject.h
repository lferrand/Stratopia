#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "movableobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class RenderableObject : public MovableObject
{
    public:
        RenderableObject();
        RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render):MovableObject(positionCarte.x,positionCarte.y),renderer(render),textureObjet(texture),positionObjetTexture(posTexture),positionObjetMap(positionCarte){}
        virtual ~RenderableObject();
        void setHealth(int h){health=h;}
        float getHealth(){return health;}
        void Render();
    protected:
    private:
        int health;

        SDL_Renderer *renderer;
        SDL_Texture *textureObjet;

        SDL_Rect positionObjetTexture;
        SDL_Rect positionObjetMap;

};

#endif // RENDERABLEOBJECT_H
