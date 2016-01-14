#include "renderableobject.h"
#include "message.h"

SDL_Texture* RenderableObject::BarreVieTexture = NULL;
SDL_Texture* RenderableObject::VieTexture = NULL;
SDL_Texture* RenderableObject::SelectionUniteTexture = NULL;
SDL_Texture* RenderableObject::SelectionUniteEnnemieTexture = NULL;





RenderableObject::RenderableObject(SDL_Rect positionCarte,SDL_Renderer *render,UnitTextures &texts, std::vector<RenderableObject*> &_objects,int _playerID,bool isEnnemy_):
MovableObject(positionCarte.x,positionCarte.y),renderer(render),positionObjetMap(positionCarte),health(100),textures(texts),objects(_objects),playerID(_playerID),isEnnemy(isEnnemy_),etapeSelection(0)
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
bool RenderableObject::IsDead()
{

    return health <= 0;
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

    if(!IsDead())
    {
        if(!symetrieSpriteNecessaire)
        {
            SDL_RenderCopy(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap);
            if(textures.projectileLance)
            {
                textures.positionActuelleProjectile.x=textures.positionActuelleProjectile.x-Camera::positionCamera.x;
                textures.positionActuelleProjectile.y=textures.positionActuelleProjectile.y-Camera::positionCamera.y;
                SDL_RenderCopy(renderer,textures.projectileTexture,&textures.positionProjectileTexture[numeroSpriteAAfficher[0]],&textures.positionActuelleProjectile);
                textures.projectileLance=false;
            }
        }
        else
        {
            SDL_RenderCopyEx(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap,0,NULL,SDL_FLIP_HORIZONTAL);
            if(textures.projectileLance)
            {
                textures.positionActuelleProjectile.x=textures.positionActuelleProjectile.x-Camera::positionCamera.x;
                textures.positionActuelleProjectile.y=textures.positionActuelleProjectile.y-Camera::positionCamera.y;
                SDL_RenderCopyEx(renderer,textures.projectileTexture,&textures.positionProjectileTexture[numeroSpriteAAfficher[0]],&textures.positionActuelleProjectile,0,NULL,SDL_FLIP_HORIZONTAL);
                textures.projectileLance=false;
            }
        }
            SDL_RenderCopy(renderer,BarreVieTexture,NULL,&positionBarreVieTexture);
            SDL_RenderCopy(renderer,VieTexture,NULL,&positionVieTexture);

            if(isSelect && !isEnnemy)
            {
                SDL_RenderCopy(renderer,SelectionUniteTexture,NULL,&positionObjetMap);
            }
            else if(isSelect && isEnnemy)
            {
                etapeSelection++;
                if(etapeSelection%20<15)
                {
                    SDL_RenderCopy(renderer,SelectionUniteEnnemieTexture,NULL,&positionObjetMap);
                }
                else if(etapeSelection>=60)
                {
                    etapeSelection=0;
                    isSelect=false;
                }
            }
    }
    else
    {
        numeroSpriteAAfficher[1]=9;
        if(!symetrieSpriteNecessaire)
        {
            SDL_RenderCopy(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap);
        }
        else
        {
            SDL_RenderCopyEx(renderer,textures.spriteTexture,&textures.positionTexture[numeroSpriteAAfficher[0]][numeroSpriteAAfficher[1]],&positionObjetMap,0,NULL,SDL_FLIP_HORIZONTAL);
        }
    }




}
void RenderableObject::CalculateDamage(int _damage)
{
    //void
}

void RenderableObject::SendMessage(RenderableObject &target, Message message)
{
    target.ReceiveMessage(message);
}
void RenderableObject::ReceiveMessage(Message message)
{
    receivedMessages.push_back(message);
}
std::vector<Message> RenderableObject::GetMessages()
{
    return receivedMessages;
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
char RenderableObject::GetType(){

}

void RenderableObject::ClearMessages()
{
    receivedMessages.clear();
}

RenderableObject::~RenderableObject()
{
    //dtor
}
