#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include "Jeu/jeu.h"
#include "mapjeu.h"
#include "mapediteur.h"
#include "tilesediteur.h"

void ChargerJeu(int taille=2);
void ChargerEditeur(int taille=2);
void ChargerMenu();

void ChargerJeu(int taille)
{
    Jeu *monJeu=new Jeu(taille);
    SDL_Event event;
    bool end = false;
    bool fini=false;
    while(!end)
    {
        if(monJeu->Fin())
        {
            fini=true;
        }
        else if(monJeu->Action())
        {
            monJeu->Render();
        }

        while(SDL_PollEvent(&event)&&!end)
        {
            if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
                delete monJeu;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)
            {
                delete monJeu;
                end=true;
            }
            else if(!fini)
            {
                monJeu->RecevoirEvent(event);
            }
        }


    }

}
void ChargerMenu()
{
    SDL_Window *menuFenetre = SDL_CreateWindow("Stratopia", 30, 30, 1024, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_Renderer *renderer= SDL_CreateRenderer(menuFenetre, -1, 0);
    SDL_Surface *menuSurface=IMG_Load("Jeu/Images/menu.bmp");
    SDL_Texture *menuTexture=SDL_CreateTextureFromSurface(renderer,menuSurface);
    SDL_FreeSurface(menuSurface);

    SDL_Event event;
    bool end = false;

    while(!end)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
        SDL_RenderPresent(renderer);
        SDL_RaiseWindow(menuFenetre);

        SDL_WaitEvent(&event);

        if(event.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                end = true;
            }
        else if(event.type=SDL_KEYDOWN)
        {
            if(event.key.keysym.sym==SDLK_1)
            {
                SDL_HideWindow(menuFenetre);
                ChargerJeu();
                SDL_ShowWindow(menuFenetre);
                SDL_RaiseWindow(menuFenetre);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
                SDL_RenderPresent(renderer);
            }
            else if(event.key.keysym.sym==SDLK_2)
            {
                SDL_HideWindow(menuFenetre);
                ChargerEditeur();
                SDL_ShowWindow(menuFenetre);
                SDL_RaiseWindow(menuFenetre);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
                SDL_RenderPresent(renderer);
            }
            else if(event.key.keysym.sym==SDLK_3)
            {
                SDL_HideWindow(menuFenetre);
                ChargerJeu(1);
                SDL_ShowWindow(menuFenetre);
                SDL_RaiseWindow(menuFenetre);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
                SDL_RenderPresent(renderer);
            }
            else if(event.key.keysym.sym==SDLK_4)
            {
                SDL_HideWindow(menuFenetre);
                ChargerEditeur(1);
                SDL_ShowWindow(menuFenetre);
                SDL_RaiseWindow(menuFenetre);
                SDL_RenderClear(renderer);
                SDL_RenderCopy(renderer,menuTexture,NULL,NULL);
                SDL_RenderPresent(renderer);
            }
            else if(event.key.keysym.sym==SDLK_ESCAPE && event.key.windowID==SDL_GetWindowID(menuFenetre))
            {
                std::cout << "mort" << std::endl;
                SDL_DestroyTexture(menuTexture);
                SDL_DestroyWindow(menuFenetre);
                end=true;
            }

        }

    }

}
void ChargerEditeur(int taille)
{
    MapEditeur *monEditeur=new MapEditeur(taille);
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
                delete mesTiles;
                delete monEditeur;
            }
            else if(event.type==SDL_KEYDOWN && event.key.keysym.sym==SDLK_ESCAPE)
            {
                delete mesTiles;
                delete monEditeur;
                end=true;
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

    //ChargerJeu();
    //ChargerEditeur();
    ChargerMenu();
    return 0;
}
