#ifndef UNITDISTANCE_H
#define UNITDISTANCE_H

#include "unit.h"


class UnitDistance : public Unit
{
    public:
        UnitDistance(char _type, bool _isJoueurUniteS,SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer,bool**pathMap);
        virtual ~UnitDistance();
        virtual void UnitMove(int x, int y);
        virtual void Attack(Unit& target);
        virtual bool Die();
    protected:
    private:
};

#endif // UNITDISTANCE_H
