#include "renderableobject.h"

SDL_Texture* RenderableObject::BarreVieTexture = NULL;
SDL_Texture* RenderableObject::VieTexture = NULL;
SDL_Texture* RenderableObject::SelectionUniteTexture = NULL;





RenderableObject::RenderableObject(SDL_Rect positionCarte,SDL_Renderer *render,UnitTextures &texts, std::vector<RenderableObject*> &_objects,int _playerID):
MovableObject(positionCarte.x,positionCarte.y),renderer(render),positionObjetMap(positionCarte),health(100),textures(texts),objects(_objects),playerID(_playerID)
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
    numeroSpriteAAfficher[0]=2;
    numeroSpriteAAfficher[1]=0;
}

void RenderableObject::Update()
{

}

int RenderableObject::GetPlayerID()
{
    return playerID;
}

void RenderableObject::Render()
{
    positionObjetMap.x=getX()-Camera::positionCamera.x;
    positionObjetMap.y=getY()-Camera::positionCamera.y;
    positionBarreVieTexture.x=positionObjetMap.x+positionObjetMap.w/2-37/2;
    positionBarreVieTexture.y=positionObjetMap.y-5;
    positionBarreVieTexture.w=37;
    positionBarreVieTexture.h=5;
    positionVieTexture.x=positionBarreVieTexture.x+1;
    positionVieTexture.y=positionBarreVieTexture.y+1;
    positionVieTexture.w=health*(positionBarreVieTexture.w-2)/100;
    positionVieTexture.h=positionBarreVieTexture.h-2;

    if(!symetrieSpriteNecessaire)
    {
        SDL_RenderCopy(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap);
    }
    else
    {
        SDL_RenderCopyEx(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap,0,NULL,SDL_FLIP_HORIZONTAL);
    }

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
