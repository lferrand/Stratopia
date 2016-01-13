#include "unitdistancehumaintexture.h"

UnitDistanceHumainTexture::UnitDistanceHumainTexture(SDL_Renderer *render):UnitTextures(render)
{
//Chargement de texture
    SDL_Surface *spriteSurface=IMG_Load("Editeur/Images/archer_sprite.png");
    SDL_Surface *projectileSurface=IMG_Load("Jeu/Images/fleche_archer.png");

    spriteTexture=SDL_CreateTextureFromSurface(renderer,spriteSurface);
    projectileTexture=SDL_CreateTextureFromSurface(renderer,projectileSurface);

    SDL_FreeSurface(spriteSurface);
    SDL_FreeSurface(projectileSurface);
    positionActuelleProjectile.w=44;
    positionActuelleProjectile.h=27;
    positionProjectileTexture.x=72;
    positionProjectileTexture.y=6;
    positionProjectileTexture.w=44;
    positionProjectileTexture.h=27;
    positionTexture=new SDL_Rect*[6];
    for(int i=0;i<6;i++)
    {
        positionTexture[i]=new SDL_Rect[9];
        for(int j=0;j<9;j++)
        {
            positionTexture[i][j].x=58*i;
            positionTexture[i][j].y=71*j+10;
            positionTexture[i][j].w=58;
            positionTexture[i][j].h=61;
        }
    }}

UnitDistanceHumainTexture::~UnitDistanceHumainTexture()
{
    //dtor
}
