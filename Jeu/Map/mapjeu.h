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
        MapJeu(SDL_Renderer *render);
        void LoadMap();
        virtual ~MapJeu();
        void Render();
    protected:
    private:
    int longueur;
    int largeur;
    SDL_Renderer *renderer;

    bool **cartePassage;
    SDL_Texture *mapTexture;


};

#endif // MAPJEU_H
