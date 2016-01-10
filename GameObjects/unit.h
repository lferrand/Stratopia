#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"
#include "../Tools/vector2d.h"

class Unit : public RenderableObject
{
    public:
        Unit(char t, bool isJoueur,SDL_Rect positionCarte,SDL_Renderer *renderer, bool **pathingMap_,UnitTextures &texts): RenderableObject(positionCarte, renderer,texts), type(t),isJoueurUnite(isJoueur),pathingMap(pathingMap_)
        {}
        virtual ~Unit();
        virtual void UnitMove();
        virtual void Attack();
        virtual void Update();
        virtual bool Die();
        Vector2D Seek(Vector2D target);
        void Move(Vector2D);
        void SetPathingMap(bool** &pathingMap);
        void SetFacing(Vector2D face);
        void SetDestination(int x, int y);
        void SetTarget(Unit* &target);

    protected:
        float attackTimer;
        float attackCD;

        int vision;
        int range;
        int damage;


        char type;
        bool isJoueurUnite;
        std::vector<Node> path;
        bool** pathingMap;
        Vector2D facing;
        Vector2D velocity;
        Vector2D *destination;
        Unit *target;
    private:

};

#endif // UNIT_H
