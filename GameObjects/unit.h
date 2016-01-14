#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"
#include <vector>
#include "../Tools/node.h"
#include "../Tools/vector2d.h"
#include "message.h"

enum {N,E,W,S,NE,NW,SE,SW};

class Unit : public RenderableObject
{
    public:
        Unit(char t, bool isJoueur,SDL_Rect positionCarte,SDL_Renderer *renderer, bool **pathingMap_,UnitTextures &texts,std::vector<RenderableObject*> &objects,int playerID):
            RenderableObject(positionCarte, renderer,texts,objects,playerID,!isJoueur), type(t),isJoueurUnite(isJoueur),pathingMap(pathingMap_),attaqueEnCours(false)
        {}
        virtual ~Unit();
        virtual void UnitMove();
        virtual bool Attack();
        virtual void Update();
        virtual bool IsDead();
        virtual bool Die();
        Vector2D Seek(Vector2D target);
        void Move(Vector2D);
        void SetPathingMap(bool** &pathingMap);
        void SetFacing(Vector2D face);
        void SetDestination(int x, int y);
        void SetNullTarget();
        void SetTarget(RenderableObject* &target);
        void SetTarget(Unit* &target);
        void SetNullDestination();
        Vector2D GetVelocity();
        Vector2D GetFacing();
        Vector2D* GetDestination();
        RenderableObject* GetTarget();
        int GetDirection();
        void ChangerSpriteDirection();
        void AnimationSpriteDeplacement();
        virtual void AnimationSpriteCombat();
        void RunAway();

        std::vector<RenderableObject*> GetPercept();
        void ClearPath();
        void DeleteTarget();
        bool DetectUnitCollision();
        Vector2D AvoidUnitCollision();
        RenderableObject* GetClosestEnemy();
        bool CanRunAway();
        bool CanAttack();
        int runAwayTimer;
        virtual char GetType();


    protected:
        float attackTimer;
        float attackCD;
        int runAwayTime;

        int vision;
        int range;
        int damage;

        bool attaqueEnCours;
        int etapeAnimation;

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
