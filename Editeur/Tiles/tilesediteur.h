#ifndef TILESEDITEUR_H
#define TILESEDITEUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TilesEditeur
{
    public:
        TilesEditeur();
        SDL_Surface *GetTilesSurface();
        virtual ~TilesEditeur();
        void RecevoirEvenement(SDL_Event event);
        SDL_Rect GetPositionTileSelectionne(){return positionTileSelectionne;}
    protected:
    private:
        SDL_Window *tileFenetre;
        SDL_Texture *textureFenetre;
        SDL_Texture *tilesTexture;
        SDL_Texture *selectionTexture;

        SDL_Surface *tilesSurface;

        SDL_Renderer *renderer;
        SDL_Rect positionTiles;
        SDL_Rect positionTileSelectionne;
};

#endif // TILESEDITEUR_H
