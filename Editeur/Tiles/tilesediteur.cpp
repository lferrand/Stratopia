#include "tilesediteur.h"

TilesEditeur::TilesEditeur()
{
    tileFenetre = SDL_CreateWindow("Stratopia Editeur Tile", 20, 30, 400, 325, SDL_WINDOW_SHOWN);
    spriteFenetre = SDL_CreateWindow("Stratopia Editeur sprite", 20, 30, 400, 325, SDL_WINDOW_HIDDEN);

    modeActuel=TILE_MODE;

    ChargerFenetreTile();
    ChargerFenetreSprite();



}

void TilesEditeur::ChargerFenetreTile()
{
    rendererTiles = SDL_CreateRenderer(tileFenetre, -1, 0);
    tilesSurface=IMG_Load("Editeur/Images/map_tiles_3.png");
    SDL_Surface *selectionSurface=IMG_Load("Editeur/Images/selection_tile.png");

    tilesTexture = SDL_CreateTextureFromSurface(rendererTiles, tilesSurface);
    selectionTexture=SDL_CreateTextureFromSurface(rendererTiles, selectionSurface);

    SDL_FreeSurface(selectionSurface);

    positionTiles.x=0;
    positionTiles.y=0;
    positionTiles.w=400;
    positionTiles.h=325;

    positionTileSelectionne.x=0;
    positionTileSelectionne.y=0;
    positionTileSelectionne.w=16;
    positionTileSelectionne.h=16;

    int w_tiles, h_tiles;
    SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);
    float ratio_w=(float)positionTiles.w/(float)w_tiles;
    float ratio_h=(float)positionTiles.h/(float)h_tiles;

    positionClic.x=0;
    positionClic.y=0;
    positionClic.w=w_tiles/16*ratio_w;
    positionClic.h=h_tiles/13*ratio_h;

    UpdateFenetreTile();
}


void TilesEditeur::ChargerFenetreSprite()
{
    rendererSprites =SDL_CreateRenderer(spriteFenetre,-1,0);

    SDL_Surface* spriteOrcSurface=IMG_Load("Editeur/Images/orc0.png");
    spriteOrcTexture=SDL_CreateTextureFromSurface(rendererSprites, spriteOrcSurface);
    positionSpriteCaC.x=37;
    positionSpriteCaC.y=37;
    positionSpriteCaC.w=75;
    positionSpriteCaC.h=75;
    positionSpriteCaCAffichage.x=37;
    positionSpriteCaCAffichage.y=37;
    positionSpriteCaCAffichage.w=15;
    positionSpriteCaCAffichage.h=15;

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
        if(event.button.windowID==SDL_GetWindowID(tileFenetre))
        {
            if(modeActuel==TILE_MODE)
            {
                int w_tiles, h_tiles;
                SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);
                float ratio_w=(float)positionTiles.w/(float)w_tiles;
                float ratio_h=(float)positionTiles.h/(float)h_tiles;

                positionClic.x=event.button.x/(int)(16*ratio_w)*(int)(16*ratio_w);
                positionClic.y=event.button.y/(int)(16*ratio_h)*(int)(16*ratio_h);


                positionClic.w=w_tiles/16*ratio_w;
                positionClic.h=h_tiles/13*ratio_h;

                positionTileSelectionne=positionClic;

                UpdateFenetreTile();
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
    SDL_RenderCopy(rendererTiles,selectionTexture,NULL,&positionClic);
    SDL_RenderPresent(rendererTiles);
}

void TilesEditeur::UpdateFenetreSprite()
{
    SDL_RenderClear(rendererSprites);
    SDL_RenderCopy(rendererSprites,spriteOrcTexture,&positionSpriteCaC,&positionSpriteCaC);
    SDL_RenderPresent(rendererSprites);
}

TilesEditeur::~TilesEditeur()
{
    SDL_FreeSurface(tilesSurface);
}

