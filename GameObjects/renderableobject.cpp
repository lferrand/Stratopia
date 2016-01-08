#include "renderableobject.h"

SDL_Texture* RenderableObject::BarreVieTexture100 = NULL;

RenderableObject::RenderableObject()
{
    //ctor
}
RenderableObject::RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render):
MovableObject(positionCarte.x,positionCarte.y),renderer(render),textureObjet(texture),positionObjetTexture(posTexture),positionObjetMap(positionCarte),health(100)
{
    positionBarreVieTexture.x=positionObjetMap.x;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=35;
    positionBarreVieTexture.h=3;

}

void RenderableObject::Render()
{
    positionObjetMap.x=getX();
    positionObjetMap.y=getY();
    SDL_RenderCopy(renderer,textureObjet,&positionObjetTexture,&positionObjetMap);
    SDL_RenderCopy(renderer,BarreVieTexture100,NULL,&positionBarreVieTexture);

}

RenderableObject::~RenderableObject()
{
    //dtor
}
