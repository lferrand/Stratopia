#include "unitdistanceorctexture.h"

UnitDistanceOrcTexture::UnitDistanceOrcTexture(SDL_Renderer *render):UnitTextures(render)
{
//Chargement de texture
    SDL_Surface *spriteSurface=IMG_Load("Editeur/Images/archer_sprite_orc.png");
    SDL_Surface *projectileSurface=IMG_Load("Jeu/Images/hache_orc.png");

    spriteTexture=SDL_CreateTextureFromSurface(renderer,spriteSurface);
    projectileTexture=SDL_CreateTextureFromSurface(renderer,projectileSurface);

    SDL_FreeSurface(spriteSurface);
    SDL_FreeSurface(projectileSurface);
    positionActuelleProjectile.w=44;
    positionActuelleProjectile.h=27;

    positionProjectileTexture=new SDL_Rect[5];

    positionProjectileTexture[0].x=9;
    positionProjectileTexture[0].y=5;
    positionProjectileTexture[0].w=14;
    positionProjectileTexture[0].h=35;

    positionProjectileTexture[1].x=40;
    positionProjectileTexture[1].y=8;
    positionProjectileTexture[1].w=31;
    positionProjectileTexture[1].h=29;

    positionProjectileTexture[2].x=75;
    positionProjectileTexture[2].y=18;
    positionProjectileTexture[2].w=41;
    positionProjectileTexture[2].h=9;

    positionProjectileTexture[3].x=121;
    positionProjectileTexture[3].y=9;
    positionProjectileTexture[3].w=31;
    positionProjectileTexture[3].h=29;

    positionProjectileTexture[4].x=168;
    positionProjectileTexture[4].y=4;
    positionProjectileTexture[4].w=14;
    positionProjectileTexture[4].h=36;


    positionTexture=new SDL_Rect*[6];
    for(int i=0;i<6;i++)
    {
        positionTexture[i]=new SDL_Rect[10];
        for(int j=0;j<9;j++)
        {
            positionTexture[i][j].x=62*i;
            positionTexture[i][j].y=54*j;
            positionTexture[i][j].w=62;
            positionTexture[i][j].h=54;
        }
        positionTexture[i][9].x=62*i;
        positionTexture[i][9].y=503;
        positionTexture[i][9].w=62;
        positionTexture[i][9].h=60;
        positionTexture[i][9].h=60;
    }
}

UnitDistanceOrcTexture::~UnitDistanceOrcTexture()
{
    //dtor
}
