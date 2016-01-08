#ifndef MAPEDITEUR_H
#define MAPEDITEUR_H
#include "tilesediteur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <list>
#include <vector>

#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20

struct UniteEditeurStr
{
    char type;
    SDL_Rect position;
};

class MapEditeur
{
    public:
        MapEditeur();
        virtual ~MapEditeur();
        void LoadMap();
        void ChangerTiles(TilesEditeur *nouveauTile);
        void NewMap();
        void RecevoirEvenement(SDL_Event event);
        void ActualiserAffichageCarte();
        void SauvegarderMap();
    protected:
    private:
        SDL_Window *editeurFenetre;
        SDL_Surface *mapSurface;
        SDL_Texture *grilleTexture;
        SDL_Texture *mapTexture;

        SDL_Texture* passageBloqueTexture;

        SDL_Texture *spriteOrcTexture;

        bool visionCarte;

        TilesEditeur *mesTiles;
        SDL_Renderer *renderer;

        int longueur;
        int largeur;

        SDL_Rect positionSourisPrecedente;

        bool **cartePassage;
        std::string **carteTexture;

        std::vector<UniteEditeurStr> uniteJoueur;
};


#endif // MAPEDITEUR_H
