#include "unittextures.h"

UnitTextures::UnitTextures(SDL_Renderer *render):renderer(render)
{
    positionActuelleProjectile.w=188;
    positionActuelleProjectile.h=51;
}

UnitTextures::~UnitTextures()
{
    SDL_DestroyTexture(spriteTexture);
    for(int i=0;i<6;i++)
    {
        delete[] positionTexture[i];
    }
    delete[] positionTexture;
    SDL_DestroyTexture(projectileTexture);
    delete[] positionProjectileTexture;
}
