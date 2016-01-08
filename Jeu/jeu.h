#ifndef JEU_H
#define JEU_H
#include <vector>
#include <iostream>
#include "mapjeu.h"
#include "../GameObjects/unit.h"

class Jeu
{
    public:
        Jeu();
        void ChargerMap();
        void ChargerUnite();
        virtual ~Jeu();
    protected:
    private:
        MapJeu *maCarte;
        SDL_Window *jeuFenetre;
        SDL_Renderer *renderer;
        std::vector<Unit> uniteJoueur;
        std::vector<Unit> uniteOrdinateur;
};

#endif // JEU_H
