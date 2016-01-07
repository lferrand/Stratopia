#include "tilesediteur.h"

TilesEditeur::TilesEditeur()
{
    tileFenetre = SDL_CreateWindow("Stratopia Editeur Tile", 20, 30, 400, 600, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(tileFenetre, -1, 0);

    tilesSurface=IMG_Load("Editeur/Images/map_tiles_3.png");
    SDL_Surface *selectionSurface=IMG_Load("Editeur/Images/selection_tile.png");

    tilesTexture = SDL_CreateTextureFromSurface(renderer, tilesSurface);
    selectionTexture=SDL_CreateTextureFromSurface(renderer, selectionSurface);


    SDL_FreeSurface(selectionSurface);


    positionTiles.x=0;
    positionTiles.y=0;
    positionTiles.w=400;
    positionTiles.h=325;

    positionTileSelectionne.x=0;
    positionTileSelectionne.y=0;
    positionTileSelectionne.w=16;
    positionTileSelectionne.h=16;

    SDL_Rect positionClic;

    int w_tiles, h_tiles;
    SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);
    float ratio_w=(float)positionTiles.w/(float)w_tiles;
    float ratio_h=(float)positionTiles.h/(float)h_tiles;

    positionClic.x=0;
    positionClic.y=0;
    positionClic.w=w_tiles/16*ratio_w;
    positionClic.h=h_tiles/13*ratio_h;





    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,tilesTexture,NULL,&positionTiles);
    SDL_RenderCopy(renderer,selectionTexture,NULL,&positionClic);

    SDL_RenderPresent(renderer);

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
            SDL_Rect positionClic;

            int w_tiles, h_tiles;
            SDL_QueryTexture(tilesTexture, NULL, NULL, &w_tiles, &h_tiles);
            float ratio_w=(float)positionTiles.w/(float)w_tiles;
            float ratio_h=(float)positionTiles.h/(float)h_tiles;

            positionClic.x=event.button.x/(int)(16*ratio_w)*(int)(16*ratio_w);
            positionClic.y=event.button.y/(int)(16*ratio_h)*(int)(16*ratio_h);


            positionClic.w=w_tiles/16*ratio_w;
            positionClic.h=h_tiles/13*ratio_h;

            positionTileSelectionne=positionClic;




            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer,tilesTexture,NULL,&positionTiles);

            SDL_RenderCopy(renderer,selectionTexture,NULL,&positionClic);
            SDL_RenderPresent(renderer);
        }
        break;
    }
}

TilesEditeur::~TilesEditeur()
{
    SDL_FreeSurface(tilesSurface);

}

