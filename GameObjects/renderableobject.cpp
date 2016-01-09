#include "renderableobject.h"

SDL_Texture* RenderableObject::BarreVieTexture = NULL;
SDL_Texture* RenderableObject::VieTexture = NULL;



RenderableObject::RenderableObject()
{
}
RenderableObject::RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render):
MovableObject(positionCarte.x,positionCarte.y),renderer(render),textureObjet(texture),positionObjetTexture(posTexture),positionObjetMap(positionCarte),health(100)
{
    positionBarreVieTexture.x=positionObjetMap.x;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=37;
    positionBarreVieTexture.h=5;
    positionVieTexture.x=positionBarreVieTexture.x+1;
    positionVieTexture.y=positionBarreVieTexture.y+1;
    positionVieTexture.w=positionBarreVieTexture.w-2;
    positionVieTexture.h=positionBarreVieTexture.h-2;


}

void RenderableObject::Render()
{
    positionObjetMap.x=getX();
    positionObjetMap.y=getY();

    positionBarreVieTexture.x=positionObjetMap.x;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=37;
    positionBarreVieTexture.h=5;
    positionVieTexture.x=positionBarreVieTexture.x+1;
    positionVieTexture.y=positionBarreVieTexture.y+1;
    positionVieTexture.w=positionBarreVieTexture.w-2;
    positionVieTexture.h=positionBarreVieTexture.h-2;

    SDL_RenderCopy(renderer,textureObjet,&positionObjetTexture,&positionObjetMap);
    SDL_RenderCopy(renderer,BarreVieTexture,NULL,&positionBarreVieTexture);

    SDL_RenderCopy(renderer,VieTexture,NULL,&positionVieTexture);
}

RenderableObject::~RenderableObject()
{
    //dtor
}
