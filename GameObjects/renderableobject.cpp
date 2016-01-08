#include "renderableobject.h"

RenderableObject::RenderableObject()
{
    //ctor
}

void RenderableObject::Render()
{
    SDL_RenderCopy(renderer,textureObjet,&positionObjetTexture,&positionObjetMap);
}

RenderableObject::~RenderableObject()
{
    //dtor
}
