#include "mapediteur.h"

MapEditeur::MapEditeur()
{
    editeurFenetre = SDL_CreateWindow("Stratopia Editeur", 450, 30, 800, 600, SDL_WINDOW_SHOWN);

    longueur=40;
    largeur=30;
    editerLieuPassage=false;
    renderer= SDL_CreateRenderer(editeurFenetre, -1, 0);
    SDL_Surface *passageBloqueSurface=IMG_Load("Editeur/Images/passage_bloque.png");
    passageBloqueTexture=SDL_CreateTextureFromSurface(renderer,passageBloqueSurface);
    SDL_FreeSurface(passageBloqueSurface);




    LoadMap();

}

void MapEditeur::ChangerTiles(TilesEditeur *nouveauTile)
{
    mesTiles=nouveauTile;
}

void MapEditeur::NewMap()
{
    SDL_Rect positionGrille;
    positionGrille.x=0;
    positionGrille.y=0;
    positionGrille.w=LARGEUR_CASE;
    positionGrille.h=HAUTEUR_CASE;

    SDL_Rect positionTile;
    positionTile.x=0;
    positionTile.y=0;
    positionTile.w=LARGEUR_CASE;
    positionTile.h=HAUTEUR_CASE;

    SDL_RenderClear(renderer);
    SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();
    mapSurface=SDL_CreateRGBSurface(0,longueur*16,largeur*16,32,0,0,0,0);
    //SDL_Texture *textureTiles=SDL_CreateTextureFromSurface(renderer, tilesSurface);

    SDL_Rect positionTileDefaut;
    positionTileDefaut.x=0;
    positionTileDefaut.y=0;
    positionTileDefaut.w=16;
    positionTileDefaut.h=16;

    for(int i=0;i<longueur;i++)
    {
        for(int j=0;j<largeur;j++)
        {
            positionGrille.x=i*16;
            positionGrille.y=j*16;
            SDL_BlitSurface(tilesSurface,&positionTileDefaut,mapSurface,&positionGrille);
        }
    }
   mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);

        SDL_RenderCopy(renderer,mapTexture,NULL,NULL);

        SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

        SDL_RenderPresent(renderer);
}

void MapEditeur::LoadMap()
{
    //Case de la grille
    SDL_Surface *caseGrilleSurface=IMG_Load("Editeur/Images/grille.png");
    SDL_Surface *grilleSurface=SDL_CreateRGBSurface(0,800,600,32,0,0,0,0);
    SDL_FillRect(grilleSurface, NULL, SDL_MapRGB(grilleSurface->format, 255, 255, 255));
    SDL_SetColorKey(grilleSurface,SDL_TRUE, SDL_MapRGB(grilleSurface->format, 255, 255, 255));

    SDL_Rect positionGrille;
    positionGrille.x=0;
    positionGrille.y=0;
    positionGrille.w=LARGEUR_CASE;
    positionGrille.h=HAUTEUR_CASE;



    cartePassage=new bool*[longueur];

    for(int i=0;i<longueur;i++)
    {
        cartePassage[i]=new bool[largeur];
        for(int j=0;j<largeur;j++)
        {
            cartePassage[i][j]=true;
            positionGrille.x=i*LARGEUR_CASE;
            positionGrille.y=j*HAUTEUR_CASE;
            SDL_BlitSurface(caseGrilleSurface,NULL,grilleSurface,&positionGrille);

        }
    }
    grilleTexture=SDL_CreateTextureFromSurface(renderer, grilleSurface);

    SDL_FreeSurface(grilleSurface);
    SDL_FreeSurface(caseGrilleSurface);

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

    SDL_RenderPresent(renderer);


}

void MapEditeur::RecevoirEvenement(SDL_Event event)
{
    switch(event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(event.button.windowID==SDL_GetWindowID(editeurFenetre))
        {


            if(editerLieuPassage)
            {
                SDL_Rect positionClic;
                positionClic.x=event.button.x/LARGEUR_CASE;
                positionClic.y=event.button.y/HAUTEUR_CASE;

                cartePassage[positionClic.x][positionClic.y]=!cartePassage[positionClic.x][positionClic.y];
                positionSourisPrecedente=positionClic;
                ActualiserAffichageCartePassage();
            }
            else
            {
            SDL_Rect positionClic;
            positionClic.x=event.button.x/LARGEUR_CASE*16;
            positionClic.y=event.button.y/HAUTEUR_CASE*16;
            positionClic.w=16;
            positionClic.h=16;

            positionSourisPrecedente=positionClic;
                SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();


                SDL_Texture *textureTiles=SDL_CreateTextureFromSurface(renderer, tilesSurface);

                SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();
                positionTileSelectionne.x/=1.5625;
                positionTileSelectionne.y/=1.5625;
                positionTileSelectionne.w/=1.5625;
                positionTileSelectionne.h/=1.5625;

                SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);
                SDL_RenderClear(renderer);

                SDL_RenderCopy(renderer,mapTexture,NULL,NULL);
                SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

                SDL_RenderPresent(renderer);
            }

        }
        break;

        case SDL_MOUSEMOTION:
            if(event.button.windowID==SDL_GetWindowID(editeurFenetre))
            {
                    if(event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        if(editerLieuPassage)
                        {
                            SDL_Rect positionClic;
                            positionClic.x=event.motion.x/LARGEUR_CASE;
                            positionClic.y=event.motion.y/HAUTEUR_CASE;

                            if(positionClic.x == positionSourisPrecedente.x &&positionClic.y == positionSourisPrecedente.y)
                            {
                                return;
                            }
                            positionSourisPrecedente=positionClic;

                            cartePassage[positionClic.x][positionClic.y]=!cartePassage[positionClic.x][positionClic.y];
                            positionSourisPrecedente=positionClic;
                            ActualiserAffichageCartePassage();
                        }
                        else
                        {
                            SDL_Rect positionClic;

                            positionClic.x=event.motion.x/LARGEUR_CASE*16;
                            positionClic.y=event.motion.y/HAUTEUR_CASE*16;
                            positionClic.w=16;
                            positionClic.h=16;
                            if(positionClic.x == positionSourisPrecedente.x &&positionClic.y == positionSourisPrecedente.y)
                            {
                                return;
                            }
                            positionSourisPrecedente=positionClic;


                            SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();


                            SDL_Texture *textureTiles=SDL_CreateTextureFromSurface(renderer, tilesSurface);

                            SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();
                            positionTileSelectionne.x/=1.5625;
                            positionTileSelectionne.y/=1.5625;
                            positionTileSelectionne.w/=1.5625;
                            positionTileSelectionne.h/=1.5625;

                            SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                            mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);
                            SDL_RenderClear(renderer);

                            SDL_RenderCopy(renderer,mapTexture,NULL,NULL);
                            SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

                            SDL_RenderPresent(renderer);
                        }
                    }
            }
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym==SDLK_F1)
            {
                editerLieuPassage=!editerLieuPassage;
            }
            if(event.key.keysym.sym==SDLK_s)
            {
                //SauvegarderMap();
            }
            break;

    }
}

void MapEditeur::ActualiserAffichageCartePassage()
{
    SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer,mapTexture,NULL,NULL);

    SDL_Rect collageTextureBloque;
    collageTextureBloque.w=LARGEUR_CASE;
    collageTextureBloque.h=HAUTEUR_CASE;
    for(int i=0; i<longueur;i++)
    {
        for(int j=0;j<largeur;j++)
        {
            if(!cartePassage[i][j])
            {
                collageTextureBloque.x=i*LARGEUR_CASE;
                collageTextureBloque.y=j*HAUTEUR_CASE;
                SDL_RenderCopy(renderer,passageBloqueTexture,NULL,&collageTextureBloque);
            }
        }
    }

    SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

    SDL_RenderPresent(renderer);
}
MapEditeur::~MapEditeur()
{
    for(int i=0;i<longueur;i++)
    {
         delete[] cartePassage[i];
    }
    delete[] cartePassage;
}
