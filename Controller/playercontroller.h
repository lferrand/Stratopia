#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include <vector>
#include "controller.h"
#include "../GameObjects/unit.h"


class PlayerController : public Controller
{
    public:
        PlayerController(std::vector<Unit*> &unites, SDL_Renderer *render):
        unitesJoueur(unites),renderer(render),selectionEnCours(false)
        {}
        virtual ~PlayerController();
        void RecevoirEvenement(SDL_Event &event);
        void CreerTextureRectangleSelection();
        void TesterIntersectionAvecJoueur();

        void Render();
    protected:
        std::vector<Unit*> &unitesJoueur;
        std::vector<Unit*> unitesSelectionnees;

        bool selectionEnCours;

        SDL_Renderer *renderer;
        SDL_Texture *selectionTexture;
        SDL_Rect positionCliqueInitial;
        SDL_Rect positionSourisActuel;
        SDL_Rect rectangleSelectionForme;
    private:
};

#endif // PLAYERCONTROLLER_H
