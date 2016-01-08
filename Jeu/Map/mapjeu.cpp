#include "mapjeu.h"
#include "../../Tools/node.h"
#include "../../Tools/tools.h"

MapJeu::MapJeu()
{
    jeuFenetre = SDL_CreateWindow("Stratopia jeu", 450, 30, 800, 600, SDL_WINDOW_SHOWN);

    longueur=40;
    largeur=30;

    renderer= SDL_CreateRenderer(jeuFenetre, -1, 0);

    LoadMap();
}

void MapJeu::LoadMap()
{
    std::ifstream fichier("carte1.lvl", std::ios::in);

    cartePassage=new bool*[longueur];


    //Chargement des textures du tile
    SDL_Surface *tilesSurface=IMG_Load("Editeur/Images/map_tiles_2.png");
    SDL_Texture *tilesTexture=SDL_CreateTextureFromSurface(renderer,tilesSurface);
    SDL_FreeSurface(tilesSurface);

    //Préparation des positions
    SDL_Rect positionTexture;
    positionTexture.w=32;
    positionTexture.h=32;
    SDL_Rect positionCollage;
    positionCollage.w=LARGEUR_CASE;
    positionCollage.h=HAUTEUR_CASE;

    SDL_RenderClear(renderer);

    //Chargement de la map
      std::string ligne;
    for(int i=0;i<longueur;i++)
    {
        cartePassage[i]=new bool[largeur];
        for(int j=0;j<largeur;j++)
        {
            positionCollage.x=i*LARGEUR_CASE;
            positionCollage.y=j*HAUTEUR_CASE;
            //Remplissage tableau de passage
            fichier>>ligne;
            if(ligne.compare("0"))
            {
                cartePassage[i][j]=false;
            }
            else
            {
                cartePassage[i][j]=true;
            }
            //Remplissage de la composante x de la texture
            fichier>>ligne;
            int result;
            std::stringstream convert(ligne);
            convert >> result;
            positionTexture.x=result*32+result;
            //Remplissage de la composante y de la texture
            fichier>>ligne;
            std::stringstream convert2(ligne);
            convert2 >> result;
            positionTexture.y=result*32+result;

            SDL_RenderCopy(renderer,tilesTexture,&positionTexture,&positionCollage);
        }
    }

    Node start = Node(7,7);
    Node endNode = Node(20,13);
    std::vector<Node> path;

    if(Tools::Astar(start,endNode,cartePassage,path)){
        std::cout << "found path";
    }

    SDL_RenderPresent(renderer);
}

MapJeu::~MapJeu()
{
    //dtor
}
