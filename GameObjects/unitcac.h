#ifndef UNITCAC2_H
#define UNITCAC2_H

#include "unit.h"
#include "tools.h"
#include "vector2d.h"
#include "aicontroller.h"

class UnitCaC : public Unit
{
    public:

        UnitCaC(char _type, bool _isJoueurUniteS,SDL_Rect positionCarte,SDL_Renderer *renderer,bool **pathMap,UnitTextures &texts,std::vector<RenderableObject*> &_objects,int playerID);
        UnitCaC(char _type, bool _isJoueurUniteS,SDL_Rect positionCarte,SDL_Renderer *renderer,bool **pathMap,AIController *_AIController,UnitTextures &texts,std::vector<RenderableObject*> &_objects,int playerID);
            virtual ~UnitCaC();
        virtual void UnitMove();
        virtual void Attack();
        virtual void Update();
        virtual bool Die();
    protected:
        AIController *AIcontroller;
    private:
};

#endif // UNITCAC_H
