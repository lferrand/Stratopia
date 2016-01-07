#ifndef MAPEDITEUR_H
#define MAPEDITEUR_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "tilesediteur.h"

#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20



class MapEditeur
{
    public:
        MapEditeur();
        virtual ~MapEditeur();
        void LoadMap();
        void ChangerTiles(TilesEditeur *nouveauTile);
        void NewMap();
        void RecevoirEvenement(SDL_Event event);
        void ActualiserAffichageCartePassage();
    protected:
    private:
        SDL_Window *editeurFenetre;
        SDL_Surface *mapSurface;
        SDL_Texture *grilleTexture;
        SDL_Texture *mapTexture;

        SDL_Texture* passageBloqueTexture;
        TilesEditeur *mesTiles;
        SDL_Renderer *renderer;

        int longueur;
        int largeur;

        bool editerLieuPassage;

        SDL_Rect positionSourisPrecedente;

        bool **cartePassage;

};

#endif // MAPEDITEUR_H