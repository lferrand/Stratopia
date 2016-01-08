#ifndef UNITCAC_H
#define UNITCAC_H

#include "unit.h"


class UnitCaC : public Unit
{
    public:
        UnitCaC();
        virtual ~UnitCaC();
        virtual void UniteMove();
        virtual void Attack(Unit target);
        virtual void Die();
    protected:
    private:
};

#endif // UNITCAC_H
