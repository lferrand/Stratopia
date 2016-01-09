#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"
#include "../Tools/vector2d.h"

class Unit : public RenderableObject
{
    public:
        Unit(char t, bool isJoueur, SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer, bool **pathingMap_): RenderableObject(texture,positionTexture,positionCarte, renderer), type(t),isJoueurUnite(isJoueur),pathingMap(pathingMap_)
        {}
        virtual ~Unit();
        virtual void UnitMove();
        virtual void Attack(Unit& target);
        virtual bool Die();
        Vector2D Seek(Vector2D target);
        void Move(Vector2D);
        void SetPathingMap(bool** &pathingMap);
        void SetFacing(Vector2D face);
        void SetDestination(int x, int y);
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
        Vector2D velocity;
        Vector2D *destination;

    private:

};

#endif // UNIT_H
