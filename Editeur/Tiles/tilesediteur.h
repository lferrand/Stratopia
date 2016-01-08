#ifndef TILESEDITEUR_H
#define TILESEDITEUR_H
#include <iostream>
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
        bool IsEnnemieSpriteSelectionne(){return isEnnemieSpriteSelectionne;}
        SDL_Rect GetPositionSpriteSelectionneSurTexture(){return positionSpriteSelectionneSurTexture;}
        char GetTypeSpriteSelectionne(){return typeSpriteSelectionne;}
        void UpdateFenetreTile();
        void UpdateFenetreSprite();

    protected:
    private:
        SDL_Window *tileFenetre;
        SDL_Window *spriteFenetre;

        SDL_Texture *textureFenetre;
        SDL_Texture *tilesTexture;
        SDL_Texture *selectionTextureTiles;
        SDL_Texture *selectionTextureSprite;
        SDL_Surface *tilesSurface;

        SDL_Texture *spriteCaCHumainTexture;
        SDL_Texture *spriteDistanceHumainTexture;
        SDL_Texture *spriteCaCOrcTexture;
        SDL_Texture *spriteDistanceOrcTexture;



        SDL_Texture *spriteOrcTexture;



        int modeActuel;
        SDL_Rect positionClic;

        SDL_Renderer *rendererTiles;
        SDL_Renderer *rendererSprites;

        SDL_Rect positionTiles;
        SDL_Rect positionTileSelectionne;

        SDL_Rect positionSpriteCaCSurTexture;
        SDL_Rect positionSpriteDistanceSurTexture;
        SDL_Rect positionSpriteDistanceEnnemieSurTexture;
        SDL_Rect positionSpriteCaCEnnemieSurTexture;


        SDL_Rect positionSpriteSelectionneSurFenetre;
        SDL_Rect positionSpriteEnnemieDistanceAffichage;


        bool isEnnemieSpriteSelectionne;
        char typeSpriteSelectionne;
        SDL_Rect positionSpriteSelectionneSurTexture;

        SDL_Rect positionSpriteCaCAffichage;
        SDL_Rect positionSpriteEnnemieCaCAffichage;
        SDL_Rect positionSpriteDistanceAffichage;

};

bool SourisDansRect(SDL_Rect &souris, SDL_Rect &zoneSelection);

#endif // TILESEDITEUR_H
