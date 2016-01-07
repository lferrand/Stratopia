#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "mapediteur.h"
#include "tilesediteur.h"


int main(int argc, char *argv[])
{
    SDL_Event event;
    bool end = false;

    MapEditeur *monEditeur=new MapEditeur();
    TilesEditeur *mesTiles=new TilesEditeur();

    monEditeur->ChangerTiles(mesTiles);
    monEditeur->NewMap();


    // Window

    // Renderer
/*
    rendererTile = SDL_CreateRenderer(Tile, -1, SDL_RENDERER_ACCELERATED);

    bitmapSurface = IMG_Load("Editeur/Images/map_tiles_2.png");
    bitmapTex = SDL_CreateTextureFromSurface(rendererTile, bitmapSurface);
    SDL_FreeSurface(bitmapSurface);
*/
    // Event loop

    while(!end)
    {
        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
        else
        {
            mesTiles->RecevoirEvenement(event);
            monEditeur->RecevoirEvenement(event);

        }

        /*SDL_RenderClear(rendererTile);
        SDL_RenderCopy(rendererTile, bitmapTex, NULL, NULL);
        SDL_RenderPresent(rendererTile);*/

    }

    return 0;
}
