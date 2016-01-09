#include "mapjeu.h"
#include "../../Tools/node.h"
#include "../../Tools/tools.h"

MapJeu::MapJeu(SDL_Renderer *render)
{
    renderer=render;
    longueur=30;
    largeur=40;

    Camera::positionCamera.x=0;
    Camera::positionCamera.y=0;
    Camera::positionCamera.w=1024;
    Camera::positionCamera.h=640;

    LoadMap();
}
void MapJeu::BougerCamera(char direction)
{
    switch(direction)
    {
    case 'd':
        if(Camera::positionCamera.x+Camera::positionCamera.w<largeur*32)
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
        if(Camera::positionCamera.y+Camera::positionCamera.h<longueur*32)
        {
            Camera::positionCamera.y+=8;
        }
        break;

    }

}

void MapJeu::Render()
{
    SDL_RenderCopy(renderer,mapTexture,&Camera::positionCamera,NULL);
}
void MapJeu::LoadMap()
{
    std::ifstream fichier("carte1.lvl", std::ios::in);

    cartePassage=new bool*[largeur];

    //Chargement des textures du tile
    SDL_Surface *tilesSurface=IMG_Load("Editeur/Images/map_tiles_2.png");
    SDL_Surface *mapSurface=SDL_CreateRGBSurface(0,largeur*32,longueur*32,32,0,0,0,0);
    //Préparation des positions
    SDL_Rect positionTexture;
    positionTexture.w=32;
    positionTexture.h=32;
    SDL_Rect positionCollage;
    positionCollage.w=32;
    positionCollage.h=32;


    //Chargement de la map
      std::string ligne;
    for(int i=0;i<largeur;i++)
    {
        cartePassage[i]=new bool[longueur];
        for(int j=0;j<longueur;j++)
        {
            positionCollage.x=i*32;
            positionCollage.y=j*32;
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

            SDL_BlitSurface(tilesSurface,&positionTexture,mapSurface ,&positionCollage);
        }
    }
    mapTexture=SDL_CreateTextureFromSurface(renderer,mapSurface),
    SDL_FreeSurface(tilesSurface);
    SDL_FreeSurface(mapSurface);
    fichier.close();
//    Node start = Node(7,7);
//    Node endNode = Node(20,13);
//    std::vector<Node> path;
//
//    if(Tools::Astar(start,endNode,cartePassage,path)){
//        std::cout << "found path";
//    }

}

MapJeu::~MapJeu()
{
    //dtor
}
