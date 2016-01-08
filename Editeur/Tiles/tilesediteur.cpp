#include "tilesediteur.h"

TilesEditeur::TilesEditeur()
{
    tileFenetre = SDL_CreateWindow("Stratopia Editeur Tile", 20, 30, 626, 659, SDL_WINDOW_SHOWN);
    spriteFenetre = SDL_CreateWindow("Stratopia Editeur sprite", 20, 30, 400, 325, SDL_WINDOW_HIDDEN);

    rendererSprites =SDL_CreateRenderer(spriteFenetre,-1,0);
    rendererTiles = SDL_CreateRenderer(tileFenetre, -1, 0);

    modeActuel=TILE_MODE;

    ChargerFenetreTile();
    ChargerFenetreSprite();



}

void TilesEditeur::ChargerFenetreTile()
{
    tilesSurface=IMG_Load("Editeur/Images/map_tiles_2.png");
    SDL_Surface *selectionSurface=IMG_Load("Editeur/Images/selection_tile.png");

    tilesTexture = SDL_CreateTextureFromSurface(rendererTiles, tilesSurface);
    selectionTextureTiles=SDL_CreateTextureFromSurface(rendererTiles, selectionSurface);
    selectionTextureSprite=SDL_CreateTextureFromSurface(rendererSprites, selectionSurface);
    SDL_FreeSurface(selectionSurface);

    positionTiles.x=0;
    positionTiles.y=0;
    positionTiles.w=626;
    positionTiles.h=659;

    positionTileSelectionne.x=1;
    positionTileSelectionne.y=1;
    positionTileSelectionne.w=32;
    positionTileSelectionne.h=32;

    int w_tiles, h_tiles;
    SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);

    positionClic.x=1;
    positionClic.y=1;
    positionClic.w=32;
    positionClic.h=32;

    UpdateFenetreTile();
}


void TilesEditeur::ChargerFenetreSprite()
{

    SDL_Surface* spriteCaCOrcSurface=IMG_Load("Editeur/Images/cac_sprite_orc.png");
    SDL_Surface* spriteCaCHumainSurface=IMG_Load("Editeur/Images/cac_sprite.png");
    SDL_Surface* spriteDistanceHumainSurface=IMG_Load("Editeur/Images/archer_sprite.png");
    SDL_Surface* spriteDistanceOrcSurface=IMG_Load("Editeur/Images/archer_sprite_orc.png");

    spriteCaCOrcTexture=SDL_CreateTextureFromSurface(rendererSprites, spriteCaCOrcSurface);
    spriteDistanceOrcTexture=SDL_CreateTextureFromSurface(rendererSprites, spriteDistanceOrcSurface);
    spriteCaCHumainTexture=SDL_CreateTextureFromSurface(rendererSprites, spriteCaCHumainSurface);
    spriteDistanceHumainTexture=SDL_CreateTextureFromSurface(rendererSprites, spriteDistanceHumainSurface);

    SDL_FreeSurface(spriteCaCOrcSurface);
    SDL_FreeSurface(spriteDistanceOrcSurface);
    SDL_FreeSurface(spriteCaCHumainSurface);
    SDL_FreeSurface(spriteDistanceHumainSurface);



    //La position des unités sur la texture
    positionSpriteCaCSurTexture.x=312;
    positionSpriteCaCSurTexture.y=5;
    positionSpriteCaCSurTexture.w=45;
    positionSpriteCaCSurTexture.h=60;

    positionSpriteDistanceSurTexture.x=240;
    positionSpriteDistanceSurTexture.y=10;
    positionSpriteDistanceSurTexture.w=50;
    positionSpriteDistanceSurTexture.h=50;

    positionSpriteCaCEnnemieSurTexture.x=312;
    positionSpriteCaCEnnemieSurTexture.y=5;
    positionSpriteCaCEnnemieSurTexture.w=45;
    positionSpriteCaCEnnemieSurTexture.h=60;

    positionSpriteDistanceEnnemieSurTexture.x=250;
    positionSpriteDistanceEnnemieSurTexture.y=10;
    positionSpriteDistanceEnnemieSurTexture.w=50;
    positionSpriteDistanceEnnemieSurTexture.h=50;

    //La position des selection d'unités sur la fenetre de selection
    positionSpriteCaCAffichage.x=0;
    positionSpriteCaCAffichage.y=0;
    positionSpriteCaCAffichage.w=75;
    positionSpriteCaCAffichage.h=75;

    positionSpriteDistanceAffichage.x=0;
    positionSpriteDistanceAffichage.y=75;
    positionSpriteDistanceAffichage.w=75;
    positionSpriteDistanceAffichage.h=75;

    positionSpriteEnnemieCaCAffichage=positionSpriteCaCAffichage;
    positionSpriteEnnemieDistanceAffichage=positionSpriteDistanceAffichage;
    positionSpriteEnnemieCaCAffichage.x=77;
    positionSpriteEnnemieDistanceAffichage.x=77;

    //selection par default
    positionSpriteSelectionneSurFenetre=positionSpriteCaCAffichage;
    isEnnemieSpriteSelectionne=false;
    typeSpriteSelectionne='c';
    positionSpriteSelectionneSurTexture=positionSpriteCaCSurTexture;



    UpdateFenetreSprite();
}

SDL_Surface* TilesEditeur::GetTilesSurface()
{
    return tilesSurface;
}

void TilesEditeur::RecevoirEvenement(SDL_Event event)
{
    switch(event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if(event.button.windowID==SDL_GetWindowID(tileFenetre)||event.button.windowID==SDL_GetWindowID(spriteFenetre))
        {
            if(modeActuel==TILE_MODE)
            {
                int w_tiles, h_tiles;
                SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);
                positionClic.x=event.button.x/34*34-1*event.button.x/34;
                positionClic.y=event.button.y/34*34-1*event.button.y/34;

                positionClic.w=32;
                positionClic.h=32;

                positionTileSelectionne=positionClic;

                UpdateFenetreTile();
            }
            else if (modeActuel==SPRITE_MODE)
            {
                positionClic.x=event.button.x;
                positionClic.y=event.button.y;
                if(SourisDansRect(positionClic,positionSpriteCaCAffichage))
                {
                    positionSpriteSelectionneSurFenetre=positionSpriteCaCAffichage;
                    positionSpriteSelectionneSurTexture=positionSpriteCaCSurTexture;
                    typeSpriteSelectionne='c';
                    isEnnemieSpriteSelectionne=false;
                    UpdateFenetreSprite();
                }
                else if(SourisDansRect(positionClic,positionSpriteDistanceAffichage))
                {
                    positionSpriteSelectionneSurFenetre=positionSpriteDistanceAffichage;
                    positionSpriteSelectionneSurTexture=positionSpriteDistanceSurTexture;
                    typeSpriteSelectionne='d';
                    isEnnemieSpriteSelectionne=false;
                    UpdateFenetreSprite();
                }
                else if(SourisDansRect(positionClic,positionSpriteEnnemieCaCAffichage))
                {
                    positionSpriteSelectionneSurFenetre=positionSpriteEnnemieCaCAffichage;
                    positionSpriteSelectionneSurTexture=positionSpriteCaCSurTexture;
                    isEnnemieSpriteSelectionne=true;
                    typeSpriteSelectionne='c';
                    UpdateFenetreSprite();
                }
                else if(SourisDansRect(positionClic,positionSpriteEnnemieDistanceAffichage))
                {
                    positionSpriteSelectionneSurFenetre=positionSpriteEnnemieDistanceAffichage;
                    positionSpriteSelectionneSurTexture=positionSpriteDistanceSurTexture;
                    typeSpriteSelectionne='d';
                    isEnnemieSpriteSelectionne=true;
                    UpdateFenetreSprite();
                }
            }
        }
        break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym==SDLK_F1)
            {
                if(modeActuel==TILE_MODE)
                {
                    SDL_HideWindow(tileFenetre);
                    SDL_ShowWindow(spriteFenetre);
                    modeActuel=SPRITE_MODE;
                    UpdateFenetreSprite();

                }
                else if (modeActuel==SPRITE_MODE||modeActuel==PASSAGE_MODE)
                {
                    SDL_HideWindow(spriteFenetre);
                    SDL_ShowWindow(tileFenetre);
                    modeActuel=TILE_MODE;
                    UpdateFenetreTile();
                }
            }
            else if(event.key.keysym.sym==SDLK_p)
            {
                SDL_HideWindow(spriteFenetre);
                SDL_HideWindow(tileFenetre);
                modeActuel=PASSAGE_MODE;
            }
        break;
    }
}
void TilesEditeur::UpdateFenetreTile()
{
    SDL_RenderClear(rendererTiles);
    SDL_RenderCopy(rendererTiles,tilesTexture,NULL,&positionTiles);
    SDL_RenderCopy(rendererTiles,selectionTextureTiles,NULL,&positionClic);
    SDL_RenderPresent(rendererTiles);
}

void TilesEditeur::UpdateFenetreSprite()
{
    SDL_RenderClear(rendererSprites);
    //SDL_SetTextureColorMod(spriteOrcTexture,100,100,255);
    SDL_RenderCopy(rendererSprites,spriteCaCHumainTexture,&positionSpriteCaCSurTexture,&positionSpriteCaCAffichage);
    SDL_RenderCopy(rendererSprites,spriteDistanceHumainTexture,&positionSpriteDistanceSurTexture,&positionSpriteDistanceAffichage);

    SDL_SetTextureColorMod(spriteOrcTexture,255,100,100);
    SDL_RenderCopy(rendererSprites,spriteCaCOrcTexture,&positionSpriteCaCEnnemieSurTexture,&positionSpriteEnnemieCaCAffichage);
    SDL_RenderCopy(rendererSprites,spriteDistanceOrcTexture,&positionSpriteDistanceEnnemieSurTexture,&positionSpriteEnnemieDistanceAffichage);


    SDL_RenderCopy(rendererSprites,selectionTextureSprite,NULL,&positionSpriteSelectionneSurFenetre);

    SDL_RenderPresent(rendererSprites);
}

TilesEditeur::~TilesEditeur()
{
    SDL_FreeSurface(tilesSurface);
}

bool SourisDansRect(SDL_Rect &souris, SDL_Rect &zoneSelection)
{
    return souris.x>=zoneSelection.x && souris.y >=zoneSelection.y && souris.x <= zoneSelection.x+zoneSelection.w && souris.y <= zoneSelection.y+zoneSelection.h;
}

