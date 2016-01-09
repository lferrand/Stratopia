#ifndef UNITCAC2_H
#define UNITCAC2_H

#include "unit.h"
#include "tools.h"
#include "vector2d.h"

class UnitCaC : public Unit
{
    public:
        UnitCaC(char, bool,SDL_Texture*, SDL_Rect, SDL_Rect,SDL_Renderer*,bool**);

        virtual ~UnitCaC();
        virtual void UnitMove(int x, int y);
        virtual void Attack(Unit& target);
        virtual bool Die();
    protected:
    private:
};

#endif // UNITCAC_H
