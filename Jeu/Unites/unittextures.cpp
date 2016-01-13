#include "unittextures.h"

UnitTextures::UnitTextures(SDL_Renderer *render):renderer(render)
{
    positionActuelleProjectile.w=188;
    positionActuelleProjectile.h=51;
}

UnitTextures::~UnitTextures()
{
    //dtor
}
