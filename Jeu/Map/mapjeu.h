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
        void LoadMiniMap();
        virtual ~MapJeu();
        void Render();
<<<<<<< HEAD
        void RenderMiniMap();
        void RecevoirEvenement(SDL_Event &event);
        void BougerCamera(char direction);
        bool **cartePassage;

=======
        bool **cartePassage;
>>>>>>> origin/master
    protected:
    private:
        int longueur;
        int largeur;
        SDL_Renderer *renderer;
<<<<<<< HEAD

=======
>>>>>>> origin/master
        SDL_Texture *mapTexture;
        SDL_Texture *uiMiniMapTexture;
        SDL_Texture *selectionMiniMapTexture;

        SDL_Rect positionSelectionMinimap;
        SDL_Rect positionMinimap;
        SDL_Rect positionUiMinimap;

};

#endif // MAPJEU_H
