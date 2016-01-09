#include "renderableobject.h"

SDL_Texture* RenderableObject::BarreVieTexture = NULL;
SDL_Texture* RenderableObject::VieTexture = NULL;
SDL_Texture* RenderableObject::SelectionUniteTexture = NULL;





RenderableObject::RenderableObject(SDL_Texture *texture, SDL_Rect posTexture,SDL_Rect positionCarte,SDL_Renderer *render):
MovableObject(positionCarte.x,positionCarte.y),renderer(render),textureObjet(texture),positionObjetTexture(posTexture),positionObjetMap(positionCarte),health(100)
{
    positionBarreVieTexture.x=positionObjetMap.x;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=37;
    positionBarreVieTexture.h=5;
    positionVieTexture.x=positionBarreVieTexture.x+1;
    positionVieTexture.y=positionBarreVieTexture.y+1;
    positionVieTexture.w=health*(positionBarreVieTexture.w-2)/100;
    positionVieTexture.h=positionBarreVieTexture.h-2;
    isSelect=false;

}

void RenderableObject::Render()
{
    positionObjetMap.x=getX()-Camera::positionCamera.x;
    positionObjetMap.y=getY()-Camera::positionCamera.y;
    positionBarreVieTexture.x=positionObjetMap.x;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=37;
    positionBarreVieTexture.h=5;
    positionVieTexture.x=positionBarreVieTexture.x+1;
    positionVieTexture.y=positionBarreVieTexture.y+1;
    positionVieTexture.w=health*(positionBarreVieTexture.w-2)/100;
    positionVieTexture.h=positionBarreVieTexture.h-2;

    SDL_RenderCopy(renderer,textureObjet,&positionObjetTexture,&positionObjetMap);
    SDL_RenderCopy(renderer,BarreVieTexture,NULL,&positionBarreVieTexture);
    SDL_RenderCopy(renderer,VieTexture,NULL,&positionVieTexture);
    if(isSelect)
    {
        SDL_RenderCopy(renderer,SelectionUniteTexture,NULL,&positionObjetMap);
    }
}

bool RenderableObject::EstDansRectangleSelection(SDL_Rect rectangleSelection)
{
    if(SDL_HasIntersection(&rectangleSelection,&positionObjetMap))
    {
        isSelect=true;
        return true;
    }
    else
    {
        isSelect=false;
        return false;
    }
}

RenderableObject::~RenderableObject()
{
    //dtor
}
