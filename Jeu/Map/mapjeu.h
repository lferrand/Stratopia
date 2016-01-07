#ifndef MAPJEU_H
#define MAPJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <sstream>


#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20


class MapJeu
{
    public:
        MapJeu();
        void LoadMap();

        virtual ~MapJeu();
    protected:
    private:
    int longueur;
    int largeur;
    SDL_Renderer *renderer;
    SDL_Window *jeuFenetre;
    bool **cartePassage;
    SDL_Texture *mapTexture;


};

#endif // MAPJEU_H
