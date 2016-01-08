#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "mapjeu.h"
#include "mapediteur.h"
#include "tilesediteur.h"
#include "jeu.h"

void ChargerJeu()
{
    Jeu *monJeu=new Jeu();
        SDL_Event event;
    bool end = false;
    while(!end)
    {
        SDL_WaitEvent(&event);
        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
    }

}


void ChargerEditeur()
{
    MapEditeur *monEditeur=new MapEditeur();
    TilesEditeur *mesTiles=new TilesEditeur();
    monEditeur->ChangerTiles(mesTiles);
    monEditeur->NewMap();
        SDL_Event event;
    bool end = false;
>>>>>>> origin/master
    while(!end)
    {
        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
        else
        {
<<<<<<< HEAD
//            mesTiles->RecevoirEvenement(event);
//            monEditeur->RecevoirEvenement(event);
=======

            mesTiles->RecevoirEvenement(event);
            monEditeur->RecevoirEvenement(event);
>>>>>>> origin/master

        }

    }

}
int main(int argc, char *argv[])
{

    ChargerJeu();
    //ChargerEditeur();
    return 0;
}
