#include "draw.h"


SDL_Texture *loadImage(char *name)
{
    /* Charge les images avec SDL Image dans une SDL_Surface */

    SDL_Surface *loadedImage = NULL;
    SDL_Texture *texture = NULL;
    loadedImage = IMG_Load(name);

    if (loadedImage != NULL)
    {
    // Conversion de l'image en texture
    texture = SDL_CreateTextureFromSurface(getrenderer(), loadedImage);

    // On se débarrasse du pointeur vers une surface
    SDL_FreeSurface(loadedImage);
    loadedImage = NULL;
    }
    else
    printf("L'image n'a pas pu être chargée! SDL_Error : %s\n", SDL_GetError());

    return texture;
}
