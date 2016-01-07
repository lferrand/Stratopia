#include "mapediteur.h"

MapEditeur::MapEditeur()
{
    editeurFenetre = SDL_CreateWindow("Stratopia Editeur", 450, 30, 800, 600, SDL_WINDOW_SHOWN);

    visionCarte=false;
    longueur=40;
    largeur=30;
    renderer= SDL_CreateRenderer(editeurFenetre, -1, 0);
    SDL_Surface *passageBloqueSurface=IMG_Load("Editeur/Images/passage_bloque.png");
    passageBloqueTexture=SDL_CreateTextureFromSurface(renderer,passageBloqueSurface);
    SDL_FreeSurface(passageBloqueSurface);

    SDL_Surface *spriteOrcSurface=IMG_Load("Editeur/Images/orc0.png");
    spriteOrcTexture=SDL_CreateTextureFromSurface(renderer,spriteOrcSurface);
    SDL_FreeSurface(spriteOrcSurface);

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


    SDL_RenderClear(renderer);
    SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();
    mapSurface=SDL_CreateRGBSurface(0,longueur*16,largeur*16,32,0,0,0,0);

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
    carteTexture=new std::string*[longueur];
    for(int i=0;i<longueur;i++)
    {
        cartePassage[i]=new bool[largeur];
        carteTexture[i]=new std::string[largeur];
        for(int j=0;j<largeur;j++)
        {
            cartePassage[i][j]=true;
            carteTexture[i][j]="0 0";
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
            if(mesTiles->GetModeActuel()==PASSAGE_MODE)
            {
                SDL_Rect positionClic;
                positionClic.x=event.button.x/LARGEUR_CASE;
                positionClic.y=event.button.y/HAUTEUR_CASE;

                cartePassage[positionClic.x][positionClic.y]=!cartePassage[positionClic.x][positionClic.y];
                positionSourisPrecedente=positionClic;
                ActualiserAffichageCarte();
            }
            else if(mesTiles->GetModeActuel()==TILE_MODE)
            {
                //récupération de la case sélectionnée
                SDL_Rect positionClic;
                positionClic.x=event.button.x/LARGEUR_CASE*16;
                positionClic.y=event.button.y/HAUTEUR_CASE*16;
                positionClic.w=16;
                positionClic.h=16;
                positionSourisPrecedente=positionClic;

                //Création texture
                SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();

                //Récupération du tile selectionné
                SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();
                positionTileSelectionne.x/=1.5625;
                positionTileSelectionne.y/=1.5625;
                positionTileSelectionne.w/=1.5625;
                positionTileSelectionne.h/=1.5625;

                //Collage du tile sur la case

                std::stringstream ss;
                ss << positionTileSelectionne.x/16;
                ss << " ";
                ss << positionTileSelectionne.y/16;
                std::string sauvegardeTexture= ss.str();
                carteTexture[event.button.x/LARGEUR_CASE][event.button.y/HAUTEUR_CASE]=sauvegardeTexture;
                SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);

                ActualiserAffichageCarte();
            }
            else if(mesTiles->GetModeActuel()==SPRITE_MODE)
            {
                SDL_Rect positionClic;
                positionClic.x=event.button.x;
                positionClic.y=event.button.y;
                positionClic.w=30;
                positionClic.h=30;
                SDL_Rect positionSpriteCaC=mesTiles->GetPositionSpriteCaC();

                SDL_RenderCopy(renderer,spriteOrcTexture,&positionSpriteCaC,&positionClic);
                SDL_RenderPresent(renderer);

            }

        }
        break;

        case SDL_MOUSEMOTION:
            if(event.button.windowID==SDL_GetWindowID(editeurFenetre))
            {
                    if(event.motion.state & SDL_BUTTON(SDL_BUTTON_LEFT))
                    {
                        if(mesTiles->GetModeActuel()==PASSAGE_MODE)
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
                            ActualiserAffichageCarte();
                        }
                        else if(mesTiles->GetModeActuel()==TILE_MODE)
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

                            SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();
                            positionTileSelectionne.x/=1.5625;
                            positionTileSelectionne.y/=1.5625;
                            positionTileSelectionne.w/=1.5625;
                            positionTileSelectionne.h/=1.5625;

                            std::stringstream ss;
                            ss << positionTileSelectionne.x/16;
                            ss << " ";
                            ss << positionTileSelectionne.y/16;
                            std::string sauvegardeTexture= ss.str();
                            carteTexture[event.button.x/LARGEUR_CASE][event.button.y/HAUTEUR_CASE]=sauvegardeTexture;

                            SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                            mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);
                            ActualiserAffichageCarte();
                        }
                        else if(mesTiles->GetModeActuel()==SPRITE_MODE)
                        {

                        }
                    }
            }
            break;
        case SDL_KEYDOWN:

            if(event.key.keysym.sym==SDLK_s)
            {
                //SauvegarderMap();
            }
            else if(event.key.keysym.sym==SDLK_m)
            {
                visionCarte=!visionCarte;
                ActualiserAffichageCarte();
            }

            break;

    }
}

void MapEditeur::ActualiserAffichageCarte()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,mapTexture,NULL,NULL);

    SDL_Rect collageTextureBloque;
    collageTextureBloque.w=LARGEUR_CASE;
    collageTextureBloque.h=HAUTEUR_CASE;

    if(!visionCarte)
    {
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
    }


    if(!visionCarte)
        SDL_RenderCopy(renderer,grilleTexture,NULL,NULL);

    SDL_RenderPresent(renderer);
}

void MapEditeur::SauvegarderMap()
{
    std::ofstream fichier("carte1.lvl", std::ios::out | std::ios::trunc);
    for(int i=0; i<longueur;i++)
    {
        for(int j=0;j<largeur;j++)
        {
            if(!cartePassage[i][j])
            {
                fichier << '0';
            }
            else
            {
                fichier << '1';
            }
            fichier << " " << carteTexture[i][j];
            fichier<< '\n';
        }


    }


}

MapEditeur::~MapEditeur()
{
    for(int i=0;i<longueur;i++)
    {
         delete[] cartePassage[i];
    }
    delete[] cartePassage;
}
