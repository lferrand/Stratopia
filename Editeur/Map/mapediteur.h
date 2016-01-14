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
#include <string>
#define LARGEUR_CASE 32
#define HAUTEUR_CASE 32

#include "camera.h"

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
        MapEditeur(int taille);
        virtual ~MapEditeur();
        void LoadMap();
        void ChangerTiles(TilesEditeur *nouveauTile);
        void NewMap();
        void RecevoirEvenement(SDL_Event &event);
        void ActualiserAffichageCarte();
        void SauvegarderMap();
        void BougerCamera(char direction);
        void LoadMiniMap();
        void RenderMiniMap();


    protected:
    private:
        SDL_Window *editeurFenetre;
        SDL_Surface *mapSurface;
        SDL_Texture *grilleTexture;
        SDL_Texture *mapTexture;
        SDL_Texture *uniteTexture;
        SDL_Texture *uniteEnnemieTexture;
        SDL_Texture* passageBloqueTexture;

        SDL_Texture *spriteCaCHumainTexture;
        SDL_Texture *spriteDistanceHumainTexture;
        SDL_Texture *spriteCaCOrcTexture;
        SDL_Texture *spriteDistanceOrcTexture;

        bool visionCarte;

        TilesEditeur *mesTiles;
        SDL_Renderer *renderer;

        int hauteur;
        int largeur;
        int taille;


        SDL_Rect positionCarte;
        SDL_Rect positionSourisPrecedente;

        SDL_Texture *uiMiniMapTexture;
        SDL_Texture *selectionMiniMapTexture;
        SDL_Rect positionSelectionMinimap;
        SDL_Rect positionMinimap;
        SDL_Rect positionUiMinimap;
        bool **cartePassage;
        std::string **carteTexture;

        std::vector<UniteEditeurStr> uniteJoueur;
        std::vector<UniteEditeurStr> uniteEnnemie;

};


#endif // MAPEDITEUR_H
