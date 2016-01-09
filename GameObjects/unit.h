#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"

class Unit : public RenderableObject
{
    public:
        Unit();
        Unit(char t, bool isJoueur, SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer): RenderableObject(texture,positionTexture,positionCarte, renderer), type(t),isJoueurUnite(isJoueur){}
        virtual ~Unit();
        virtual void UnitMove(int x, int y);
        virtual void Attack(Unit& target);
        virtual bool Die();
    protected:
        float attackTimer;
        float attackCD;
        int range;
        int damage;
        char type;
        bool isJoueurUnite;
        std::vector<Node> path;
    private:

};

#endif // UNIT_H
