#ifndef JEU_H
#define JEU_H
#include <vector>
#include <iostream>
#include "mapjeu.h"

#include "unitcac.h"
#include "unitdistance.h"

#include "Unites/unitcachumaintexture.h"
#include "Unites/unitcacorctexture.h"

#include "playercontroller.h"
#include "task.h"
#include "aicontroller.h"
#include "Explore.h"

class Jeu
{
    public:
        Jeu();
        void ChargerMap();
        void ChargerUnite();
        void RecevoirEvent(SDL_Event event);
        void Render();
        void Action();
        virtual ~Jeu();
    protected:
    private:
        //Gestion du temps
        int startTick;
        int tempsAAttendre;
        int tempsEcoule;
        int masqueDirection;
        MapJeu *maCarte;
        SDL_Window *jeuFenetre;
        SDL_Renderer *renderer;
        PlayerController *joueurControlleur;
        UnitCaCHumainTexture *humainCaCTextures;
        UnitCaCOrcTexture *orcCaCTextures;
        std::vector<Unit*> uniteJoueur;
        std::vector<Unit*> uniteOrdinateur;
};

#endif // JEU_H
