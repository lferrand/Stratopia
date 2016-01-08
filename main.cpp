#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Jeu\Map\mapjeu.h"
#include "mapediteur.h"
#include "tilesediteur.h"



int main(int argc, char *argv[])
{
    SDL_Event event;
    bool end = false;

    MapJeu *mapjeu = new MapJeu();
//    MapEditeur *monEditeur=new MapEditeur();
//    TilesEditeur *mesTiles=new TilesEditeur();
//
//    monEditeur->ChangerTiles(mesTiles);
//    monEditeur->NewMap();


    while(!end)
    {
        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
        else
        {
//            mesTiles->RecevoirEvenement(event);
//            monEditeur->RecevoirEvenement(event);

        }

    }

    return 0;
}
