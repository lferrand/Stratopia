#ifndef UNIT_H
#define UNIT_H

#include "renderableobject.h"


class Unit : public RenderableObject
{
    public:
        Unit();
        Unit(char t, bool isJoueur, SDL_Texture *texture, SDL_Rect positionTexture, SDL_Rect positionCarte,SDL_Renderer *renderer): RenderableObject(texture,positionTexture,positionCarte, renderer), type(t),isJoueurUnite(isJoueur){}
        virtual ~Unit();
    protected:
    private:
        char type;
        bool isJoueurUnite;
};

#endif // UNIT_H
