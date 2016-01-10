#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Jeu/jeu.h"
#include "mapjeu.h"
#include "mapediteur.h"
#include "tilesediteur.h"


void ChargerJeu()
{
    Jeu *monJeu=new Jeu();
    SDL_Event event;
    bool end = false;
    while(!end)
    {
        monJeu->Action();
        monJeu->Render();

        while(SDL_PollEvent(&event)&&!end)
        {
            if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
            else
            {
                monJeu->RecevoirEvent(event);
            }
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

    }

}
int main(int argc, char *argv[])
{

    ChargerJeu();
    //ChargerEditeur();
    return 0;
}
