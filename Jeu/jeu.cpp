#include "jeu.h"

Jeu::Jeu(int t)
{
    jeuFenetre = SDL_CreateWindow("Stratopia jeu", 30, 30, 1024, 640, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer= SDL_CreateRenderer(jeuFenetre, -1, 0);
    joueurControlleur=new PlayerController(uniteJoueur,uniteOrdinateur,renderer);
    startTick=-1;
    tempsEcoule=0;
    taille=t;
    humainCaCTextures=new UnitCaCHumainTexture(renderer);
    orcCaCTextures=new UnitCaCOrcTexture(renderer);
    humainDistanceTextures=new UnitDistanceHumainTexture(renderer);
    orcDistanceTextures=new UnitDistanceOrcTexture(renderer);

    tempsAAttendre=17;
    ChargerMap();
    ChargerUnite();
}

void Jeu::ChargerMap()
{
    maCarte=new MapJeu(renderer,jeuFenetre,uniteJoueur,uniteOrdinateur,taille);
}

void Jeu::ChargerUnite()
{
    //Creation des textures:


    //Chargement des textures de la barre de vie et de selections
    SDL_Surface *barreVieSurface=IMG_Load("Jeu/Images/barre_vie.png");
    SDL_Surface *vieSurface=IMG_Load("Jeu/Images/vie.png");
    SDL_Surface *selectionSurface=IMG_Load("Jeu/Images/selection_unite.png");
    SDL_Surface *selectionSurfaceEnnemie=IMG_Load("Jeu/Images/selection_unite_ennemie.png");

    RenderableObject::BarreVieTexture = SDL_CreateTextureFromSurface(renderer,barreVieSurface);
    RenderableObject::VieTexture = SDL_CreateTextureFromSurface(renderer,vieSurface);
    RenderableObject::SelectionUniteTexture = SDL_CreateTextureFromSurface(renderer,selectionSurface);
    RenderableObject::SelectionUniteEnnemieTexture = SDL_CreateTextureFromSurface(renderer,selectionSurfaceEnnemie);

    SDL_FreeSurface(selectionSurfaceEnnemie);
    SDL_FreeSurface(selectionSurface);
    SDL_FreeSurface(barreVieSurface);
    SDL_FreeSurface(vieSurface);

    std::string nomFichier;
    if(taille==1)
    {
        nomFichier="Save/unite1.lvl";
    }
    else
    {
        nomFichier="Save/unite2.lvl";
    }
    std::ifstream fichier(nomFichier.c_str(), std::ios::in);
    std::string mot;
    while(fichier >> mot && mot[0] !='-')
    {
        char type=mot[0];


        SDL_Rect positionUnitSurCarte;
        positionUnitSurCarte.h=humainCaCTextures->positionTexture[0][0].h;
        positionUnitSurCarte.w=humainCaCTextures->positionTexture[0][0].w;

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
                UnitDistance *unite=new UnitDistance(type,true,positionUnitSurCarte,renderer,maCarte->cartePassage,*humainDistanceTextures,objects,1);
                uniteJoueur.push_back(unite);
                objects.push_back(unite);

            }
            else if(type=='c')
            {

                UnitCaC *unite= new UnitCaC(type,true,positionUnitSurCarte,renderer,maCarte->cartePassage,*humainCaCTextures,objects,1);
                uniteJoueur.push_back(unite);
                objects.push_back(unite);
            }

    }

    while(fichier >> mot)
    {

        char type=mot[0];
        SDL_Rect positionUnitSurCarte;
        positionUnitSurCarte.h=orcCaCTextures->positionTexture[0][0].h;
        positionUnitSurCarte.w=orcCaCTextures->positionTexture[0][0].w;

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
                std::vector<Task*>* tasks = new std::vector<Task*>();
                Explore* explore = new Explore("explore");
                Attack* attack = new Attack("attack");
                tasks->push_back(explore);
                tasks->push_back(attack);
                AIController* contro = new AIController(*tasks);
                UnitCaC *unite =new UnitCaC(type,false,positionUnitSurCarte,renderer,maCarte->cartePassage,contro,*orcCaCTextures,objects,2);
                uniteOrdinateur.push_back(unite);
                objects.push_back(unite);
            }
            else if(type=='d')
            {
                std::vector<Task*>* tasks = new std::vector<Task*>();
                Explore* explore = new Explore("explore");
                Attack* attack = new Attack("attack");
                tasks->push_back(explore);
                tasks->push_back(attack);
                AIController* contro = new AIController(*tasks);
                UnitDistance *unite = new UnitDistance(type,false,positionUnitSurCarte,renderer,maCarte->cartePassage,contro,*orcDistanceTextures,objects,2);
                uniteOrdinateur.push_back(unite);
                objects.push_back(unite);
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
        if(!maCarte->RecevoirEvenement(event))
        {
            joueurControlleur->RecevoirEvenement(event);
        }
    }
}

bool Jeu::Action()
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


        for(int i=0;i<uniteJoueur.size();i++)
        {
            uniteJoueur[i]->Update();
        }
        for(int i=0;i<uniteOrdinateur.size();i++)
        {
            uniteOrdinateur[i]->Update();
        }
        return true;
    }
    else
    {
        return false;
    }

}
Jeu::~Jeu()
{
    delete joueurControlleur;
    delete maCarte;
}
