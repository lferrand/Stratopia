#ifndef MAPEDITEUR_H
#define MAPEDITEUR_H
#include "tilesediteur.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>

#define LARGEUR_CASE 20
#define HAUTEUR_CASE 20

struct UniteEditeurStr
{
    char type;
    bool isUniteJoueur;
    SDL_Rect positionUnite;
    SDL_Rect positionTexture;
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

        SDL_Texture *spriteCaCHumainTexture;
        SDL_Texture *spriteDistanceHumainTexture;
        SDL_Texture *spriteCaCOrcTexture;
        SDL_Texture *spriteDistanceOrcTexture;

        bool visionCarte;

        TilesEditeur *mesTiles;
        SDL_Renderer *renderer;

        int longueur;
        int largeur;

        SDL_Rect positionSourisPrecedente;

        bool **cartePassage;
        std::string **carteTexture;

        std::vector<UniteEditeurStr> uniteJoueur;
        std::vector<UniteEditeurStr> uniteEnnemie;

};


#endif // MAPEDITEUR_H
