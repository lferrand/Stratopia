#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H
#include "tools.h"
#include "movableobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Camera.h"
#include "../Jeu/Unites/unittextures.h"
class RenderableObject : public MovableObject
{
    public:
        RenderableObject(SDL_Rect positionCarte,SDL_Renderer *render,UnitTextures &textures, std::vector<RenderableObject*> &objects, int playerID);
        virtual ~RenderableObject();
        void setHealth(int h){health=h;}
        float getHealth(){return health;}
        void Render();
        void SetIsSelect(bool isSelect_){isSelect=isSelect_;}
        int GetPlayerID();
        bool EstDansRectangleSelection(SDL_Rect rectangle);
        virtual void Update();
        virtual bool IsDead();
        //texture de barre de vie
        static SDL_Texture* BarreVieTexture;
        static SDL_Texture* VieTexture;
        static SDL_Texture* SelectionUniteTexture;


    protected:
        int health;

        int numeroSpriteAAfficher[2];
        bool symetrieSpriteNecessaire;
        SDL_Renderer *renderer;

        std::vector<RenderableObject*> &objects;
        UnitTextures &textures;

        int playerID;
        bool isSelect;

        SDL_Rect positionObjetMap;
        SDL_Rect positionBarreVieTexture;
        SDL_Rect positionVieTexture;

    private:



};

#endif // RENDERABLEOBJECT_H
