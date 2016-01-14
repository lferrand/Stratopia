#ifndef MAPJEU_H
#define MAPJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include"camera.h"

#define LARGEUR_CASE 32
#define HAUTEUR_CASE 32
#include "unit.h"

class MapJeu
{
    public:
        MapJeu();
        MapJeu(SDL_Renderer *render, SDL_Window *w,std::vector<Unit*> &uniteJ,std::vector<Unit*> &uniteO,int taille);
        void LoadMap();
        void LoadMiniMap();
        virtual ~MapJeu();
        void Render();
        void RenderMiniMap();
        bool RecevoirEvenement(SDL_Event &event);
        void BougerCamera(char direction);
        bool **cartePassage;

    protected:
    private:
        int longueur;
        int largeur;
        SDL_Window *fenetre;
        SDL_Renderer *renderer;
        SDL_Texture *mapTexture;
        SDL_Texture *uniteTexture;
        SDL_Texture *uniteEnnemieTexture;
        SDL_Texture *uiMiniMapTexture;
        SDL_Texture *selectionMiniMapTexture;
        int taille;
        std::vector<Unit*> &uniteJoueur;
        std::vector<Unit*> &uniteOrdinateur;

        bool actionMiniMapEnCours;

        SDL_Rect positionSelectionMinimap;
        SDL_Rect positionCarteJeu;
        SDL_Rect positionMinimap;
        SDL_Rect positionUiMinimap;

};

#endif // MAPJEU_H
