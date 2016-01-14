#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H
#include "tools.h"
#include "movableobject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Camera.h"
#include "../Jeu/Unites/unittextures.h"

class Message;

class RenderableObject : public MovableObject
{
    public:
        RenderableObject(SDL_Rect positionCarte,SDL_Renderer *render,UnitTextures &textures, std::vector<RenderableObject*> &objects, int playerID,bool isEnnemy_);
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
        static SDL_Texture* SelectionUniteEnnemieTexture;

        void SendMessage(RenderableObject &target, Message message);
        void ReceiveMessage(Message message);
        std::vector<Message> GetMessages();
        void ClearMessages();
        virtual char GetType();
        virtual void CalculateDamage(int _damage);


    protected:
        int health;

        int numeroSpriteAAfficher[2];
        bool symetrieSpriteNecessaire;
        SDL_Renderer *renderer;

        std::vector<RenderableObject*> &objects;
        std::vector<Message> receivedMessages;
        UnitTextures &textures;

        int playerID;
        bool isSelect;
        bool isEnnemy;
        char type;

        int etapeSelection;

        SDL_Rect positionObjetMap;
        SDL_Rect positionBarreVieTexture;
        SDL_Rect positionVieTexture;

    private:



};

#endif // RENDERABLEOBJECT_H
