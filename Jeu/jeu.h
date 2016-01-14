#ifndef JEU_H
#define JEU_H
#include <vector>
#include <iostream>
#include "mapjeu.h"

#include "unitcac.h"
#include "renderableobject.h"
#include "unitdistance.h"

#include "Unites/unitcachumaintexture.h"
#include "Unites/unitcacorctexture.h"
#include "Unites/unitdistancehumaintexture.h"
#include "Unites/unitdistanceorctexture.h"


#include "playercontroller.h"
#include "task.h"
#include "aicontroller.h"
#include "Explore.h"
#include "attack.h"

class Jeu
{
    public:
        Jeu(int t);
        void ChargerMap();
        void ChargerUnite();
        void RecevoirEvent(SDL_Event event);
        void Render();
        bool Action();
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
        int taille;
        UnitDistanceOrcTexture *orcDistanceTextures;
        UnitDistanceHumainTexture *humainDistanceTextures;
        UnitCaCHumainTexture *humainCaCTextures;
        UnitCaCOrcTexture *orcCaCTextures;

        std::vector<RenderableObject*> objects;
        std::vector<Unit*> uniteJoueur;
        std::vector<Unit*> uniteOrdinateur;
};

#endif // JEU_H
