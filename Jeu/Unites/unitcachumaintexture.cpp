#include "unitcachumaintexture.h"

UnitCaCHumainTexture::UnitCaCHumainTexture(SDL_Renderer *render):UnitTextures(render)
{
    //Chargement de texture
    SDL_Surface *spriteSurface=IMG_Load("Editeur/Images/cac_sprite.png");

    spriteTexture=SDL_CreateTextureFromSurface(renderer,spriteSurface);
    SDL_FreeSurface(spriteSurface);

    positionTexture=new SDL_Rect*[6];
    for(int i=0;i<5;i++)
    {
        positionTexture[i]=new SDL_Rect[10];
        for(int j=0;j<9;j++)
        {
            positionTexture[i][j].x=74*i;
            positionTexture[i][j].y=53*j+4;
            positionTexture[i][j].w=74;
            positionTexture[i][j].h=58;
        }
        positionTexture[i][9].x=74*i;
        positionTexture[i][9].y=521;
        positionTexture[i][9].w=74;
        positionTexture[i][9].h=55;
    }




}

UnitCaCHumainTexture::~UnitCaCHumainTexture()
{
    //dtor
}
