#ifndef MAPJEU_H
#define MAPJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include"camera.h"

#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20


class MapJeu
{
    public:
        MapJeu();
        MapJeu(SDL_Renderer *render);
        void LoadMap();
        virtual ~MapJeu();
        void Render();
        void BougerCamera(char direction);
        bool **cartePassage;

    protected:
    private:
        int longueur;
        int largeur;
        SDL_Renderer *renderer;
        SDL_Texture *mapTexture;
        bool debug;


};

#endif // MAPJEU_H
