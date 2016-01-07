#ifndef TILESEDITEUR_H
#define TILESEDITEUR_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

enum {SPRITE_MODE, TILE_MODE, PASSAGE_MODE};

class TilesEditeur
{
    public:
        TilesEditeur();
        void ChargerFenetreTile();
        void ChargerFenetreSprite();

        SDL_Surface *GetTilesSurface();
        virtual ~TilesEditeur();
        void RecevoirEvenement(SDL_Event event);

        SDL_Rect GetPositionTileSelectionne(){return positionTileSelectionne;}
        int GetModeActuel(){return modeActuel;}
        SDL_Rect GetPositionSpriteCaC(){return positionSpriteCaC;}
        void UpdateFenetreTile();
        void UpdateFenetreSprite();

    protected:
    private:
        SDL_Window *tileFenetre;
        SDL_Window *spriteFenetre;

        SDL_Texture *textureFenetre;
        SDL_Texture *tilesTexture;
        SDL_Texture *selectionTexture;
        SDL_Texture *spriteOrcTexture;
        SDL_Texture *spriteOrcEnnemieTexture;
        SDL_Surface *tilesSurface;

        int modeActuel;
        SDL_Rect positionClic;

        SDL_Renderer *rendererTiles;
        SDL_Renderer *rendererSprites;

        SDL_Rect positionTiles;
        SDL_Rect positionTileSelectionne;

        SDL_Rect positionSpriteCaC;
        SDL_Rect positionSpriteCaCAffichage;
};

#endif // TILESEDITEUR_H
