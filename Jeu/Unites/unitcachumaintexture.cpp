#include "unitcachumaintexture.h"

UnitCaCHumainTexture::UnitCaCHumainTexture(SDL_Renderer *render):UnitTextures(render)
{
    //Chargement de texture
    SDL_Surface *spriteSurface=IMG_Load("Editeur/Images/cac_sprite.png");

    spriteTexture=SDL_CreateTextureFromSurface(renderer,spriteSurface);
    SDL_FreeSurface(spriteSurface);

    positionTexture=new SDL_Rect*[6];
    for(int i=0;i<6;i++)
    {
        positionTexture[i]=new SDL_Rect[9];
        for(int j=0;j<9;j++)
        {
            positionTexture[i][j].x=74*i;
            positionTexture[i][j].y=58*j;
            positionTexture[i][j].w=74;
            positionTexture[i][j].h=58;
        }
    }




}

UnitCaCHumainTexture::~UnitCaCHumainTexture()
{
    //dtor
}
