#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "movableobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class RenderableObject : public MovableObject
{
    public:
        RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render);
        virtual ~RenderableObject();
        void setHealth(int h){health=h;}
        float getHealth(){return health;}
        void Render();
        void SetIsSelect(bool isSelect_){isSelect=isSelect_;}
        bool EstDansRectangleSelection(SDL_Rect rectangle);

        //texture de barre de vie
        static SDL_Texture* BarreVieTexture;
        static SDL_Texture* VieTexture;
        static SDL_Texture* SelectionUniteTexture;


    protected:
        int health;

        SDL_Renderer *renderer;
        SDL_Texture *textureObjet;

        bool isSelect;

        SDL_Rect positionObjetTexture;
        SDL_Rect positionObjetMap;

        SDL_Rect positionBarreVieTexture;
        SDL_Rect positionVieTexture;

    private:



};

#endif // RENDERABLEOBJECT_H
