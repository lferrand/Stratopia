#ifndef JEU_H
#define JEU_H
#include <vector>
#include <iostream>
#include "mapjeu.h"

#include "unitcac.h"

#include "unitdistance.h"

#include "playercontroller.h"


class Jeu
{
    public:
        Jeu();
        void ChargerMap();
        void ChargerUnite();
        void RecevoirEvent(SDL_Event event);
        void Render();
        virtual ~Jeu();
    protected:
    private:
        MapJeu *maCarte;
        SDL_Window *jeuFenetre;
        SDL_Renderer *renderer;
        PlayerController *joueurControlleur;
        std::vector<Unit> uniteJoueur;
        std::vector<Unit> uniteOrdinateur;
};

#endif // JEU_H
