#ifndef UNITCAC_H
#define UNITCAC_H

#include "unit.h"


class UnitCaC : public Unit
{
    public:
        UnitCaC();
        UnitCaC(float _attackTimer, float _attackCD , int _range, int _damage, char _type, bool _isJoueurUnite);
        virtual ~UnitCaC();
        virtual void UnitMove();
        virtual void Attack(Unit& target);
        virtual bool Die();
    protected:
    private:
};

#endif // UNITCAC_H
