#include "jeu.h"

Jeu::Jeu()
{
    jeuFenetre = SDL_CreateWindow("Stratopia jeu", 30, 30, 1024, 640, SDL_WINDOW_SHOWN);
    renderer= SDL_CreateRenderer(jeuFenetre, -1, 0);
    joueurControlleur=new PlayerController(uniteJoueur,renderer);
    startTick=-1;
    tempsEcoule=0;
    tempsAAttendre=17;
    ChargerMap();
    ChargerUnite();
}

void Jeu::ChargerMap()
{
    maCarte=new MapJeu(renderer);
}

void Jeu::ChargerUnite()
{
    //Chargement des textures de la barre de vie et de selections
    SDL_Surface *barreVieSurface=IMG_Load("Jeu/Images/barre_vie.png");
    SDL_Surface *vieSurface=IMG_Load("Jeu/Images/vie.png");
    SDL_Surface *selectionSurface=IMG_Load("Jeu/Images/selection_unite.png");

    RenderableObject::BarreVieTexture = SDL_CreateTextureFromSurface(renderer,barreVieSurface);
    RenderableObject::VieTexture = SDL_CreateTextureFromSurface(renderer,vieSurface);
    RenderableObject::SelectionUniteTexture = SDL_CreateTextureFromSurface(renderer,selectionSurface);

    SDL_FreeSurface(selectionSurface);
    SDL_FreeSurface(barreVieSurface);
    SDL_FreeSurface(vieSurface);

    //Chargement des textures des unités
    SDL_Surface* spriteCaCOrcSurface=IMG_Load("Editeur/Images/cac_sprite_orc.png");
    SDL_Surface* spriteCaCHumainSurface=IMG_Load("Editeur/Images/cac_sprite.png");
    SDL_Surface* spriteDistanceHumainSurface=IMG_Load("Editeur/Images/archer_sprite.png");
    SDL_Surface* spriteDistanceOrcSurface=IMG_Load("Editeur/Images/archer_sprite_orc.png");

    SDL_Texture* spriteCaCOrcTexture=SDL_CreateTextureFromSurface(renderer, spriteCaCOrcSurface);
    SDL_Texture* spriteDistanceOrcTexture=SDL_CreateTextureFromSurface(renderer, spriteDistanceOrcSurface);
    SDL_Texture* spriteCaCHumainTexture=SDL_CreateTextureFromSurface(renderer, spriteCaCHumainSurface);
    SDL_Texture* spriteDistanceHumainTexture=SDL_CreateTextureFromSurface(renderer, spriteDistanceHumainSurface);

    SDL_FreeSurface(spriteCaCOrcSurface);
    SDL_FreeSurface(spriteDistanceOrcSurface);
    SDL_FreeSurface(spriteCaCHumainSurface);
    SDL_FreeSurface(spriteDistanceHumainSurface);

    //La position des unités sur la texture

    SDL_Rect positionSpriteCaCSurTexture;
    SDL_Rect positionSpriteDistanceSurTexture;
    SDL_Rect positionSpriteCaCEnnemieSurTexture;
    SDL_Rect positionSpriteDistanceEnnemieSurTexture;

     positionSpriteCaCSurTexture.x=312;
     positionSpriteCaCSurTexture.y=5;
     positionSpriteCaCSurTexture.w=45;
     positionSpriteCaCSurTexture.h=60;

     positionSpriteDistanceSurTexture.x=240;
     positionSpriteDistanceSurTexture.y=10;
     positionSpriteDistanceSurTexture.w=50;
     positionSpriteDistanceSurTexture.h=50;

     positionSpriteCaCEnnemieSurTexture.x=312;
     positionSpriteCaCEnnemieSurTexture.y=5;
     positionSpriteCaCEnnemieSurTexture.w=45;
     positionSpriteCaCEnnemieSurTexture.h=60;

     positionSpriteDistanceEnnemieSurTexture.x=250;
     positionSpriteDistanceEnnemieSurTexture.y=10;
     positionSpriteDistanceEnnemieSurTexture.w=50;
     positionSpriteDistanceEnnemieSurTexture.h=50;

    std::ifstream fichier("unite1.lvl", std::ios::in);
    std::string mot;
    while(fichier >> mot && mot[0] !='-')
    {
        char type=mot[0];
        SDL_Texture *unitTexture;
        SDL_Rect positionUnitSurTexture;
        SDL_Rect positionUnitSurCarte;
        positionUnitSurCarte.h=40;
        positionUnitSurCarte.w=40;
        if(type=='c')
        {
            unitTexture=spriteCaCHumainTexture;
            positionUnitSurTexture=positionSpriteCaCSurTexture;
        }
        else
        {
            unitTexture=spriteDistanceHumainTexture;
            positionUnitSurTexture=positionSpriteDistanceSurTexture;
        }

            fichier >> mot;
            int result;
            std::stringstream convert(mot);
            convert >> result;
            positionUnitSurCarte.x=result;

            //Remplissage de la composante y de la texture
            fichier>>mot;
            std::stringstream convert2(mot);
            convert2 >> result;
            positionUnitSurCarte.y=result;

            if(type=='d')
            {
                UnitDistance unite(type,true,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer,maCarte->cartePassage);
                uniteJoueur.push_back(&unite);

            }
            else if(type=='c')
            {
                UnitCaC unite(type,true,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer,maCarte->cartePassage);
                uniteJoueur.push_back(&unite);

            }

    }

    while(fichier >> mot)
    {
        char type=mot[0];
        SDL_Texture *unitTexture;
        SDL_Rect positionUnitSurTexture;
        SDL_Rect positionUnitSurCarte;
        positionUnitSurCarte.h=40;
        positionUnitSurCarte.w=40;
        if(type=='c')
        {
            unitTexture=spriteCaCOrcTexture;
            positionUnitSurTexture=positionSpriteCaCEnnemieSurTexture;
        }
        else
        {
            unitTexture=spriteDistanceOrcTexture;
            positionUnitSurTexture=positionSpriteDistanceEnnemieSurTexture;
        }

            fichier >> mot;
            int result;
            std::stringstream convert(mot);
            convert >> result;
            positionUnitSurCarte.x=result;

            //Remplissage de la composante y de la texture
            fichier>>mot;
            std::stringstream convert2(mot);
            convert2 >> result;
            positionUnitSurCarte.y=result;
            if(type=='c')
            {
               UnitCaC unite(type,false,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer,maCarte->cartePassage);
                uniteOrdinateur.push_back(&unite);

            }
            else if(type=='d')
            {
                UnitDistance unite(type,false,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer,maCarte->cartePassage);
                uniteOrdinateur.push_back(&unite);

            }
    }
    fichier.close();

}

void Jeu::Render()
{
    SDL_RenderClear(renderer);
    maCarte->Render();
    for(unsigned int i=0;i<uniteJoueur.size();i++)
    {
        uniteJoueur[i]->Render();
    }
    for(unsigned int i=0;i<uniteOrdinateur.size();i++)
    {

        uniteOrdinateur[i]->Render();
    }
    joueurControlleur->Render();
    maCarte->RenderMiniMap();
    SDL_RenderPresent(renderer);
}


void Jeu::RecevoirEvent(SDL_Event event)
{
    if(event.type==SDL_KEYDOWN)
    {
        if(event.key.keysym.sym==SDLK_RIGHT)
        {
            maCarte->BougerCamera('d');
        }
        if(event.key.keysym.sym==SDLK_LEFT)
        {
            maCarte->BougerCamera('g');
        }
                if(event.key.keysym.sym==SDLK_UP)
        {
            maCarte->BougerCamera('h');
        }
                if(event.key.keysym.sym==SDLK_DOWN)
        {
            maCarte->BougerCamera('b');
        }
    }
    else
    {
        joueurControlleur->RecevoirEvenement(event);
        maCarte->RecevoirEvenement(event);
    }
}

void Jeu::Action()
{
    if(startTick<0)
    {
        startTick=SDL_GetTicks();
    }
    tempsEcoule=SDL_GetTicks()-startTick;
    if(tempsEcoule>=tempsAAttendre)
    {
        tempsEcoule=tempsEcoule-tempsAAttendre;
        startTick=-1;

        /*Executer l'action ici*/


    }

}
Jeu::~Jeu()
{
    delete joueurControlleur;
    delete maCarte;
}
