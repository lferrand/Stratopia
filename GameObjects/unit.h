#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"
#include "../Tools/vector2d.h"

class Unit : public RenderableObject
{
    public:
        Unit();
        Unit(char t, bool isJoueur, SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer): RenderableObject(texture,positionTexture,positionCarte, renderer), type(t),isJoueurUnite(isJoueur){}
        virtual ~Unit();
        virtual void UnitMove(int x, int y);
        virtual void Attack(Unit& target);
        virtual bool Die();
        Vector2D Seek(Vector2D target);
        void Move(Vector2D);
    protected:
        float attackTimer;
        float attackCD;
        int range;
        int damage;
        char type;
        bool isJoueurUnite;
        std::vector<Node> path;
        bool** pathingMap;
        Vector2D facing;

    private:

};

#endif // UNIT_H
