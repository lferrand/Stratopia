#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"
#include "../Tools/vector2d.h"

enum {N,E,W,S,NE,NW,SE,SW};

class Unit : public RenderableObject
{
    public:
        Unit(char t, bool isJoueur,SDL_Rect positionCarte,SDL_Renderer *renderer, bool **pathingMap_,UnitTextures &texts,std::vector<RenderableObject*> &objects,int playerID): RenderableObject(positionCarte, renderer,texts,objects,playerID), type(t),isJoueurUnite(isJoueur),pathingMap(pathingMap_)
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
        void SetTarget(RenderableObject* &target);
        Vector2D GetVelocity();
        Vector2D GetFacing();
        Vector2D* GetDestination();
        int GetDirection();
        void ChangerSprite(int direct,char action='m');
        std::vector<RenderableObject*> GetPercept();
        void ClearPath();

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
        RenderableObject *target;
    private:

};

#endif // UNIT_H
