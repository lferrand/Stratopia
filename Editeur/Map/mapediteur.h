#ifndef MAPEDITEUR_H
#define MAPEDITEUR_H
#include "tilesediteur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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
        void SauvegarderMap();
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
        std::string **carteTexture;

};

#endif // MAPEDITEUR_H
