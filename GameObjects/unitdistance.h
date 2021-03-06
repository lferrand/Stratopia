#ifndef UNITDISTANCE_H
#define UNITDISTANCE_H

#include "unit.h"
#include "aicontroller.h"


class UnitDistance : public Unit
{
    public:
        UnitDistance(char _type, bool _isJoueurUniteS,SDL_Rect positionCarte,SDL_Renderer *renderer,bool**pathMap,UnitTextures &texts,std::vector<RenderableObject*> &_objects,int playerID);
        UnitDistance(char _type, bool _isJoueurUniteS,SDL_Rect positionCarte,SDL_Renderer *renderer,bool **pathMap,AIController *_AIController,UnitTextures &texts,std::vector<RenderableObject*> &_objects,int _playerID);
        virtual ~UnitDistance();
        virtual void UnitMove();
        virtual bool Attack();
        virtual void AnimationSpriteCombat();
        virtual void Update();
        virtual bool Die();

    protected:
        AIController *AIcontroller;
    private:
};

#endif // UNITDISTANCE_H
