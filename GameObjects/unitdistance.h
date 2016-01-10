#ifndef UNITDISTANCE_H
#define UNITDISTANCE_H

#include "unit.h"
#include "aicontroller.h"


class UnitDistance : public Unit
{
    public:
        UnitDistance(char _type, bool _isJoueurUniteS,SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer,bool**pathMap);
        virtual ~UnitDistance();
        virtual void UnitMove();
        virtual void Attack();
        virtual void Update();
        virtual bool Die();
    protected:
        AIController *AIcontroller;
    private:
};

#endif // UNITDISTANCE_H
