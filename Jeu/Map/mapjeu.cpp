#include "mapjeu.h"
#include "../../Tools/node.h"
#include "../../Tools/tools.h"

MapJeu::MapJeu(SDL_Renderer *render)
{
    renderer=render;
    longueur=30;
    largeur=40;
    positionMinimap.x=800;
    positionMinimap.y=10;
    positionMinimap.h=200;
    positionMinimap.w=200;

    positionSelectionMinimap.x=800;
    positionSelectionMinimap.y=10;
    positionSelectionMinimap.h=138;
    positionSelectionMinimap.w=160;


    positionUiMinimap.x=795;
    positionUiMinimap.y=5;
    positionUiMinimap.h=210;
    positionUiMinimap.w=210;
    Camera::positionCamera.x=0;
    Camera::positionCamera.y=0;
    Camera::positionCamera.w=1024;
    Camera::positionCamera.h=640;

    actionMiniMapEnCours=false;

    LoadMap();
    LoadMiniMap();
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

void MapJeu::RenderMiniMap()
{
    SDL_RenderCopy(renderer,uiMiniMapTexture,NULL,&positionUiMinimap);
    SDL_RenderCopy(renderer,mapTexture,NULL,&positionMinimap);
    positionSelectionMinimap.x=Camera::positionCamera.x*200/1248+positionMinimap.x;
    positionSelectionMinimap.y=Camera::positionCamera.y*200/1024+positionMinimap.y;
    SDL_RenderCopy(renderer,selectionMiniMapTexture,NULL,&positionSelectionMinimap);
}

bool MapJeu::RecevoirEvenement(SDL_Event &event)
{
    if(event.type==SDL_MOUSEBUTTONDOWN && (event.button.state& SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        SDL_Point souris;
        souris.x=event.button.x;
        souris.y=event.button.y;
        if(SDL_PointInRect(&souris,&positionMinimap))
        {
            actionMiniMapEnCours=true;
            souris.x-=positionMinimap.x;
            souris.y-=positionMinimap.y;

            Camera::positionCamera.x=souris.x*1248/200;
            if(Camera::positionCamera.x+Camera::positionCamera.w>1248)
            {
                Camera::positionCamera.x=1248-Camera::positionCamera.w;
            }
            Camera::positionCamera.y=souris.y*960/200;
            if(Camera::positionCamera.y+Camera::positionCamera.h>960)
            {
                Camera::positionCamera.y=960-Camera::positionCamera.h;
            }
        }
    }
    else if(event.type == SDL_MOUSEMOTION)
    {
        if(event.motion.state& SDL_BUTTON(SDL_BUTTON_LEFT))
        {
            SDL_Point souris;
            souris.x=event.motion.x;
            souris.y=event.motion.y;
            if(SDL_PointInRect(&souris,&positionMinimap))
            {
                actionMiniMapEnCours=true;
                souris.x-=positionMinimap.x;
                souris.y-=positionMinimap.y;

                Camera::positionCamera.x=souris.x*1248/200;
                if(Camera::positionCamera.x+Camera::positionCamera.w>1248)
                {
                    Camera::positionCamera.x=1248-Camera::positionCamera.w;
                }
                Camera::positionCamera.y=souris.y*960/200;
                if(Camera::positionCamera.y+Camera::positionCamera.h>960)
                {
                    Camera::positionCamera.y=960-Camera::positionCamera.h;
                }
            }
        }
    }
    else if(event.type==SDL_MOUSEBUTTONUP&&(event.motion.state& SDL_BUTTON(SDL_BUTTON_LEFT)))
    {
        actionMiniMapEnCours=false;
    }
    return actionMiniMapEnCours;
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

            if(ligne.compare("0")==0)
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


void MapJeu::LoadMiniMap()
{
     SDL_Surface *miniMapSurface=IMG_Load("Jeu/Images/ui_minimap.png");
     SDL_Surface *selectionMiniMapSurface=IMG_Load("Jeu/Images/selection_minimap.png");

     uiMiniMapTexture=SDL_CreateTextureFromSurface(renderer,miniMapSurface);
     selectionMiniMapTexture=SDL_CreateTextureFromSurface(renderer,selectionMiniMapSurface);

     SDL_FreeSurface(miniMapSurface);
     SDL_FreeSurface(selectionMiniMapSurface);


}
MapJeu::~MapJeu()
{
    //dtor
}
