#include "jeu.h"

Jeu::Jeu()
{
    jeuFenetre = SDL_CreateWindow("Stratopia jeu", 450, 30, 800, 600, SDL_WINDOW_SHOWN);
    renderer= SDL_CreateRenderer(jeuFenetre, -1, 0);
    joueurControlleur=new PlayerController(uniteJoueur,renderer);
    ChargerMap();
    ChargerUnite();
}

void Jeu::ChargerMap()
{
    maCarte=new MapJeu(renderer);
}

void Jeu::ChargerUnite()
{
    //Chargement des textures de la barre de vie
    SDL_Surface *barreVieSurface=IMG_Load("Jeu/Images/barre_vie.png");
    SDL_Surface *vieSurface=IMG_Load("Jeu/Images/vie.png");
    RenderableObject::BarreVieTexture = SDL_CreateTextureFromSurface(renderer,barreVieSurface);
    RenderableObject::VieTexture = SDL_CreateTextureFromSurface(renderer,vieSurface);
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

            Unit unite(type,true,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer);

            uniteJoueur.push_back(unite);
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

            Unit unite(type,false,unitTexture,positionUnitSurTexture,positionUnitSurCarte,renderer);
            uniteOrdinateur.push_back(unite);
    }

}

void Jeu::Render()
{
    SDL_RenderClear(renderer);
    maCarte->Render();
    for(int i=0;i<uniteJoueur.size();i++)
    {
        uniteJoueur[i].Render();
    }
    for(int i=0;i<uniteOrdinateur.size();i++)
    {

        uniteOrdinateur[i].Render();
    }
    joueurControlleur->Render();
    SDL_RenderPresent(renderer);
}


void Jeu::RecevoirEvent(SDL_Event event)
{
    joueurControlleur->RecevoirEvenement(event);
}

Jeu::~Jeu()
{
    //dtor
}
