#include "mapjeu.h"

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

}

MapJeu::~MapJeu()
{
    //dtor
}
