#ifndef UNITTEXTURES_H
#define UNITTEXTURES_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class UnitTextures
{
    public:
        UnitTextures(SDL_Renderer *render);

        SDL_Texture *spriteTexture;
        SDL_Rect **positionTexture;


        virtual ~UnitTextures();
    protected:
        SDL_Renderer *renderer;
    private:
};

#endif // UNITTEXTURES_H
