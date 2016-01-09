#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "movableobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class RenderableObject : public MovableObject
{
    public:
        RenderableObject();
        RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render);
        virtual ~RenderableObject();
        void setHealth(int h){health=h;}
        float getHealth(){return health;}
        void Render();

        static SDL_Texture* BarreVieTexture100;

    protected:
        int health;

        SDL_Renderer *renderer;
        SDL_Texture *textureObjet;


        SDL_Rect positionObjetTexture;
        SDL_Rect positionObjetMap;

        SDL_Rect positionBarreVieTexture;
    private:


};

#endif // RENDERABLEOBJECT_H
