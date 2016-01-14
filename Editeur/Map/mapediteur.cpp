#include "mapediteur.h"

MapEditeur::MapEditeur(int taille)
{
    editeurFenetre = SDL_CreateWindow("Stratopia Editeur", 20, 30, 1248, 640, SDL_WINDOW_SHOWN);
    Camera::positionCamera.x=0;
    Camera::positionCamera.y=0;
    Camera::positionCamera.w=1024;
    Camera::positionCamera.h=640;
    this->taille=taille;
    positionCarte=Camera::positionCamera;

    visionCarte=false;
    if(taille==1)
    {
        largeur=32;
        hauteur=20;
    }
    else if(taille==2)
    {
        largeur=64;
        hauteur=40;
    }

    renderer= SDL_CreateRenderer(editeurFenetre, -1, 0);

    //Chargement surface
    SDL_Surface *passageBloqueSurface=IMG_Load("Editeur/Images/passage_bloque.png");
    passageBloqueTexture=SDL_CreateTextureFromSurface(renderer,passageBloqueSurface);
    SDL_FreeSurface(passageBloqueSurface);

    //Chargement des sprites des unités
    SDL_Surface* spriteCaCOrcSurface=IMG_Load("Editeur/Images/cac_sprite_orc.png");
    SDL_Surface* spriteCaCHumainSurface=IMG_Load("Editeur/Images/cac_sprite.png");
    SDL_Surface* spriteDistanceHumainSurface=IMG_Load("Editeur/Images/archer_sprite.png");
    SDL_Surface* spriteDistanceOrcSurface=IMG_Load("Editeur/Images/archer_sprite_orc.png");

    spriteCaCOrcTexture=SDL_CreateTextureFromSurface(renderer, spriteCaCOrcSurface);
    spriteDistanceOrcTexture=SDL_CreateTextureFromSurface(renderer, spriteDistanceOrcSurface);
    spriteCaCHumainTexture=SDL_CreateTextureFromSurface(renderer, spriteCaCHumainSurface);
    spriteDistanceHumainTexture=SDL_CreateTextureFromSurface(renderer, spriteDistanceHumainSurface);

    SDL_FreeSurface(spriteCaCOrcSurface);
    SDL_FreeSurface(spriteDistanceOrcSurface);
    SDL_FreeSurface(spriteCaCHumainSurface);
    SDL_FreeSurface(spriteDistanceHumainSurface);

    positionUiMinimap.x=1024;
    positionUiMinimap.y=0;
    positionUiMinimap.h=640;
    positionUiMinimap.w=224;

    positionMinimap.x=positionUiMinimap.x+20;
    positionMinimap.y=positionUiMinimap.y+5;
    positionMinimap.h=positionUiMinimap.w-40;
    positionMinimap.w=positionUiMinimap.w-40;


    positionSelectionMinimap.x=positionMinimap.x;
    positionSelectionMinimap.y=positionMinimap.y;
    positionSelectionMinimap.h=Camera::positionCamera.h*positionMinimap.h/(hauteur*HAUTEUR_CASE);
    positionSelectionMinimap.w=Camera::positionCamera.w*positionMinimap.w/(largeur*LARGEUR_CASE);

    LoadMap();
    LoadMiniMap();


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
    mapSurface=SDL_CreateRGBSurface(0,largeur*LARGEUR_CASE,hauteur*HAUTEUR_CASE,32,0,0,0,0);

    SDL_Rect positionTileDefaut;
    positionTileDefaut.x=0;
    positionTileDefaut.y=429;
    positionTileDefaut.w=LARGEUR_CASE;
    positionTileDefaut.h=HAUTEUR_CASE;

    for(int i=0;i<largeur;i++)
    {
        for(int j=0;j<hauteur;j++)
        {
            positionGrille.x=i*LARGEUR_CASE;
            positionGrille.y=j*HAUTEUR_CASE;
            SDL_BlitSurface(tilesSurface,&positionTileDefaut,mapSurface,&positionGrille);
        }
    }
   mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);

        SDL_RenderCopy(renderer,mapTexture,&Camera::positionCamera,&positionCarte);

        SDL_RenderCopy(renderer,grilleTexture,&Camera::positionCamera,&positionCarte);
        RenderMiniMap();
        SDL_RenderPresent(renderer);
}

void MapEditeur::LoadMap()
{
    //Case de la grille
    SDL_Surface *caseGrilleSurface=IMG_Load("Editeur/Images/grille.png");
    SDL_Surface *grilleSurface=SDL_CreateRGBSurface(0,largeur*LARGEUR_CASE,hauteur*HAUTEUR_CASE,32,0,0,0,0);
    SDL_FillRect(grilleSurface, NULL, SDL_MapRGB(grilleSurface->format, 255, 255, 255));
    SDL_SetColorKey(grilleSurface,SDL_TRUE, SDL_MapRGB(grilleSurface->format, 255, 255, 255));

    SDL_Rect positionGrille;
    positionGrille.x=0;
    positionGrille.y=0;
    positionGrille.w=LARGEUR_CASE;
    positionGrille.h=HAUTEUR_CASE;



    cartePassage=new bool*[largeur];
    carteTexture=new std::string*[largeur];
    for(int i=0;i<largeur;i++)
    {
        cartePassage[i]=new bool[hauteur];
        carteTexture[i]=new std::string[hauteur];
        for(int j=0;j<hauteur;j++)
        {
            cartePassage[i][j]=true;
            carteTexture[i][j]="0 14";
            positionGrille.x=i*LARGEUR_CASE;
            positionGrille.y=j*HAUTEUR_CASE;
            SDL_BlitSurface(caseGrilleSurface,NULL,grilleSurface,&positionGrille);
        }
    }
    grilleTexture=SDL_CreateTextureFromSurface(renderer, grilleSurface);

    SDL_FreeSurface(grilleSurface);
    SDL_FreeSurface(caseGrilleSurface);

}

void MapEditeur::RecevoirEvenement(SDL_Event &event)
{
    switch(event.type)
    {
    case SDL_MOUSEBUTTONDOWN:

        if(event.button.windowID==SDL_GetWindowID(editeurFenetre))
        {
            SDL_Point souris;
            souris.x=event.button.x;
            souris.y=event.button.y;
            if(SDL_PointInRect(&souris,&positionMinimap))
            {
                souris.x-=positionMinimap.x;
                souris.y-=positionMinimap.y;

                Camera::positionCamera.x=souris.x*LARGEUR_CASE*largeur/positionMinimap.w;
                if(Camera::positionCamera.x+Camera::positionCamera.w>LARGEUR_CASE*largeur)
                {
                    Camera::positionCamera.x=LARGEUR_CASE*largeur-Camera::positionCamera.w;
                }
                Camera::positionCamera.y=souris.y*HAUTEUR_CASE*hauteur/positionMinimap.h;
                if(Camera::positionCamera.y+Camera::positionCamera.h>HAUTEUR_CASE*hauteur)
                {
                    Camera::positionCamera.y=HAUTEUR_CASE*hauteur-Camera::positionCamera.h;
                }
                ActualiserAffichageCarte();
            }
            else
            {

            if(mesTiles->GetModeActuel()==PASSAGE_MODE)
            {
                SDL_Rect positionClic;
                positionClic.x=(event.button.x+Camera::positionCamera.x)/LARGEUR_CASE;
                positionClic.y=(event.button.y+Camera::positionCamera.y)/HAUTEUR_CASE;

                cartePassage[positionClic.x][positionClic.y]=!cartePassage[positionClic.x][positionClic.y];
                positionSourisPrecedente=positionClic;
                ActualiserAffichageCarte();
            }
            else if(mesTiles->GetModeActuel()==TILE_MODE)
            {
                //récupération de la case sélectionnée
                SDL_Rect positionClic;
                positionClic.x=(event.button.x+Camera::positionCamera.x)/LARGEUR_CASE*32;
                positionClic.y=(event.button.y+Camera::positionCamera.y)/HAUTEUR_CASE*32;
                positionClic.w=32;
                positionClic.h=32;
                positionSourisPrecedente=positionClic;

                //Création texture
                SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();
                //Récupération du tile selectionné
                SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();

                //Collage du tile sur la case
                std::stringstream ss;
                ss << positionTileSelectionne.x/32;
                ss << " ";
                ss << positionTileSelectionne.y/32;
                std::string sauvegardeTexture= ss.str();
                carteTexture[event.button.x/LARGEUR_CASE][event.button.y/HAUTEUR_CASE]=sauvegardeTexture;
                SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                SDL_DestroyTexture(mapTexture);
                mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);

                ActualiserAffichageCarte();
            }
            else if(mesTiles->GetModeActuel()==SPRITE_MODE)
            {
                SDL_Rect positionClic;
                positionClic.x=event.button.x+Camera::positionCamera.x;
                positionClic.y=event.button.y+Camera::positionCamera.y;
                positionClic.w=40;
                positionClic.h=40;
                SDL_Rect positionSpriteSelectionne=mesTiles->GetPositionSpriteSelectionneSurTexture();
                UniteEditeurStr unit;
                unit.type=mesTiles->GetTypeSpriteSelectionne();
                unit.positionUnite=positionClic;
                unit.positionTexture=positionSpriteSelectionne;
                unit.isUniteJoueur=!mesTiles->IsEnnemieSpriteSelectionne();
                if(unit.isUniteJoueur)
                {
                    uniteJoueur.push_back(unit);
                }
                else
                {
                    uniteEnnemie.push_back(unit);
                }
                ActualiserAffichageCarte();
            }
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
                            positionClic.x=(event.motion.x+Camera::positionCamera.x)/LARGEUR_CASE;
                            positionClic.y=(event.motion.y+Camera::positionCamera.y)/HAUTEUR_CASE;

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

                            positionClic.x=(event.motion.x+Camera::positionCamera.x)/LARGEUR_CASE*32;
                            positionClic.y=(event.motion.y+Camera::positionCamera.y)/HAUTEUR_CASE*32;
                            positionClic.w=32;
                            positionClic.h=32;
                            if(positionClic.x == positionSourisPrecedente.x &&positionClic.y == positionSourisPrecedente.y)
                            {
                                return;
                            }
                            positionSourisPrecedente=positionClic;

                            SDL_Surface *tilesSurface=mesTiles->GetTilesSurface();

                            SDL_Rect positionTileSelectionne=mesTiles->GetPositionTileSelectionne();

                            std::stringstream ss;
                            ss << positionTileSelectionne.x/32;
                            ss << " ";
                            ss << positionTileSelectionne.y/32;
                            std::string sauvegardeTexture= ss.str();
                            carteTexture[event.button.x/LARGEUR_CASE][event.button.y/HAUTEUR_CASE]=sauvegardeTexture;

                            SDL_BlitSurface(tilesSurface,&positionTileSelectionne,mapSurface,&positionClic);
                            SDL_DestroyTexture(mapTexture);
                            mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface);
                            ActualiserAffichageCarte();
                        }
                    }
            }
            break;
        case SDL_KEYDOWN:

            if(event.key.keysym.sym==SDLK_s)
            {
                SauvegarderMap();
            }
            else if(event.key.keysym.sym==SDLK_m)
            {
                visionCarte=!visionCarte;
                ActualiserAffichageCarte();
            }
            else if(event.key.keysym.sym==SDLK_RIGHT)
            {
                BougerCamera('d');
            }
            else if(event.key.keysym.sym==SDLK_LEFT)
            {
                BougerCamera('g');
            }
            else if(event.key.keysym.sym==SDLK_UP)
            {
                BougerCamera('h');
            }
            else if(event.key.keysym.sym==SDLK_DOWN)
            {
                BougerCamera('b');
            }
                break;

    }
}

void MapEditeur::RenderMiniMap()
{
    SDL_RenderCopy(renderer,uiMiniMapTexture,NULL,&positionUiMinimap);
    SDL_RenderCopy(renderer,mapTexture,NULL,&positionMinimap);
    for(int i=0;i<uniteJoueur.size();i++)
    {
        SDL_Rect positionUniteMiniMap;
        positionUniteMiniMap.x=uniteJoueur[i].positionUnite.x*positionMinimap.w/(largeur*LARGEUR_CASE)+positionMinimap.x;
        positionUniteMiniMap.y=uniteJoueur[i].positionUnite.y*positionMinimap.h/(hauteur*HAUTEUR_CASE)+positionMinimap.y;
        positionUniteMiniMap.h=5;
        positionUniteMiniMap.w=5;
        SDL_RenderCopy(renderer,uniteTexture,NULL,&positionUniteMiniMap);
    }
        for(int i=0;i<uniteEnnemie.size();i++)
    {
        SDL_Rect positionUniteMiniMap;
        positionUniteMiniMap.x=uniteEnnemie[i].positionUnite.x*positionMinimap.w/(largeur*LARGEUR_CASE)+positionMinimap.x;
        positionUniteMiniMap.y=uniteEnnemie[i].positionUnite.y*positionMinimap.h/(hauteur*HAUTEUR_CASE)+positionMinimap.y;
        positionUniteMiniMap.h=5;
        positionUniteMiniMap.w=5;
        SDL_RenderCopy(renderer,uniteEnnemieTexture,NULL,&positionUniteMiniMap);
    }

    positionSelectionMinimap.x=Camera::positionCamera.x*positionMinimap.w/(largeur*LARGEUR_CASE)+positionMinimap.x;
    positionSelectionMinimap.y=Camera::positionCamera.y*positionMinimap.h/(hauteur*HAUTEUR_CASE)+positionMinimap.y;
    SDL_RenderCopy(renderer,selectionMiniMapTexture,NULL,&positionSelectionMinimap);
}
void MapEditeur::LoadMiniMap()
{
     SDL_Surface *miniMapSurface=IMG_Load("Jeu/Images/ui_minimap.png");
     SDL_Surface *selectionMiniMapSurface=IMG_Load("Jeu/Images/selection_minimap.png");
     SDL_Surface *uniteSurface=SDL_CreateRGBSurface(0,3,3,32,0,0,0,0);
     SDL_FillRect(uniteSurface,NULL,SDL_MapRGB(uniteSurface->format,0,255,0));
     uniteTexture=SDL_CreateTextureFromSurface(renderer,uniteSurface);
     SDL_FillRect(uniteSurface,NULL,SDL_MapRGB(uniteSurface->format,255,0,0));
     uniteEnnemieTexture=SDL_CreateTextureFromSurface(renderer,uniteSurface);

     uiMiniMapTexture=SDL_CreateTextureFromSurface(renderer,miniMapSurface);
     selectionMiniMapTexture=SDL_CreateTextureFromSurface(renderer,selectionMiniMapSurface);

     SDL_FreeSurface(uniteSurface);
     SDL_FreeSurface(miniMapSurface);
     SDL_FreeSurface(selectionMiniMapSurface);


}
void MapEditeur::BougerCamera(char direction)
{
        switch(direction)
        {
        case 'd':
        if(Camera::positionCamera.x+Camera::positionCamera.w<largeur*LARGEUR_CASE)
        {
            Camera::positionCamera.x+=8;
        }
        break;
    case 'g':
        if(Camera::positionCamera.x>0)
        {
            Camera::positionCamera.x-=8;
        }
        break;
    case 'h':
        if(Camera::positionCamera.y>0)
        {
            Camera::positionCamera.y-=8;
        }
        break;
    case 'b':
        if(Camera::positionCamera.y+Camera::positionCamera.h<hauteur*HAUTEUR_CASE)
        {
            Camera::positionCamera.y+=8;
        }
        break;
    }
    ActualiserAffichageCarte();
}
void MapEditeur::ActualiserAffichageCarte()
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer,mapTexture,&Camera::positionCamera,&positionCarte);

    SDL_Rect collageTextureBloque;
    collageTextureBloque.w=LARGEUR_CASE;
    collageTextureBloque.h=HAUTEUR_CASE;

    if(!visionCarte)
    {
        for(int i=0; i<largeur;i++)
        {
            for(int j=0;j<hauteur;j++)
            {
                if(!cartePassage[i][j])
                {
                    collageTextureBloque.x=i*LARGEUR_CASE-Camera::positionCamera.x;
                    collageTextureBloque.y=j*HAUTEUR_CASE-Camera::positionCamera.y;
                    SDL_RenderCopy(renderer,passageBloqueTexture,NULL,&collageTextureBloque);
                }
            }
        }
    }
    for(int unsigned i=0;i<uniteJoueur.size();i++)
    {
        SDL_Rect positionObjetMap=uniteJoueur[i].positionUnite;
        positionObjetMap.x-=Camera::positionCamera.x;
        positionObjetMap.y-=Camera::positionCamera.y;
        if(uniteJoueur[i].type=='c')
        {
            SDL_RenderCopy(renderer,spriteCaCHumainTexture,&uniteJoueur[i].positionTexture,&positionObjetMap);
        }
        else if(uniteJoueur[i].type=='d')
        {
            SDL_RenderCopy(renderer,spriteDistanceHumainTexture,&uniteJoueur[i].positionTexture,&positionObjetMap);
        }
    }
    for(int unsigned i=0;i<uniteEnnemie.size();i++)
    {
        SDL_Rect positionObjetMap=uniteEnnemie[i].positionUnite;
        positionObjetMap.x-=Camera::positionCamera.x;
        positionObjetMap.y-=Camera::positionCamera.y;
        if(uniteEnnemie[i].type=='c')
        {
            SDL_RenderCopy(renderer,spriteCaCOrcTexture,&uniteEnnemie[i].positionTexture,&positionObjetMap);
        }
        else if(uniteEnnemie[i].type=='d')
        {
            SDL_RenderCopy(renderer,spriteDistanceOrcTexture,&uniteEnnemie[i].positionTexture,&positionObjetMap);
        }
    }

    if(!visionCarte)
        SDL_RenderCopy(renderer,grilleTexture,&Camera::positionCamera,&positionCarte);
    RenderMiniMap();

    SDL_RenderPresent(renderer);
}

void MapEditeur::SauvegarderMap()
{
    std::string nomFicher;
    std::string nomFicherUnite;
    if(taille==1)
    {
        nomFicher="Save/carte1.lvl";
        nomFicherUnite="Save/unite1.lvl";
    }
    else
    {
        nomFicher="Save/carte2.lvl";
        nomFicherUnite="Save/unite2.lvl";
    }
    std::ofstream fichier(nomFicher.c_str(), std::ios::out | std::ios::trunc);

    for(int i=0; i<largeur;i++)
    {
        for(int j=0;j<hauteur;j++)
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
    fichier.close();
    fichier.open(nomFicherUnite.c_str(), std::ios::out | std::ios::trunc);
    for(unsigned int i=0;i<uniteJoueur.size();i++)
    {
        fichier << uniteJoueur[i].type << " " << uniteJoueur[i].positionUnite.x << " " << uniteJoueur[i].positionUnite.y << '\n';
    }
    fichier << "-\n";
    for(unsigned int i=0;i<uniteEnnemie.size();i++)
    {
        fichier << uniteEnnemie[i].type << " " << uniteEnnemie[i].positionUnite.x << " " << uniteEnnemie[i].positionUnite.y << '\n';
    }
    fichier.close();


}

MapEditeur::~MapEditeur()
{
    for(int i=0;i<largeur;i++)
    {
         delete[] cartePassage[i];
    }
    delete[] cartePassage;
    SDL_FreeSurface(mapSurface);

    SDL_DestroyTexture(grilleTexture);
    SDL_DestroyTexture(mapTexture);
    SDL_DestroyTexture(uniteTexture);
    SDL_DestroyTexture(uniteEnnemieTexture);
    SDL_DestroyTexture(passageBloqueTexture);
    SDL_DestroyTexture(spriteCaCHumainTexture);
    SDL_DestroyTexture(spriteDistanceHumainTexture);
    SDL_DestroyTexture(spriteCaCOrcTexture);
    SDL_DestroyTexture(spriteDistanceOrcTexture);
    SDL_DestroyTexture(uiMiniMapTexture);
    SDL_DestroyTexture(selectionMiniMapTexture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(editeurFenetre);
}
