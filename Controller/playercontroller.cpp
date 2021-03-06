#include "playercontroller.h"



PlayerController::~PlayerController()
{
    //dtor
}

void PlayerController::RecevoirEvenement(SDL_Event &event)
{
    switch(event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                positionCliqueInitial.x=event.button.x;
                positionCliqueInitial.y=event.button.y;
                rectangleSelectionForme.x=positionCliqueInitial.x;
                rectangleSelectionForme.y=positionCliqueInitial.y;
                rectangleSelectionForme.w=1;
                rectangleSelectionForme.h=1;
                TesterIntersectionAvecJoueur();
            }
            else if(event.button.button==SDL_BUTTON_RIGHT)
            {
                Unit *target=NULL;
                SDL_Rect selection;
                selection.x=event.button.x;
                selection.y=event.button.y;
                selection.w=1;
                selection.h=1;
                for(int i=0;i<unitesOrdinateur.size();i++)
                {
                    if(unitesOrdinateur[i]->EstDansRectangleSelection(selection))
                    {
                        target=unitesOrdinateur[i];
                    }
                }
                for(int i=0;i<unitesSelectionnees.size();i++)
                {
                    selection.x+=Camera::positionCamera.x;
                    selection.y+=Camera::positionCamera.y;
                    //Vector2D direction(selection.x,selection.y);
                    if(target!=NULL)
                    {
                        unitesSelectionnees[i]->SetTarget(target);
                    }
                    else
                    {
                        unitesSelectionnees[i]->SetTarget(target);
                        unitesSelectionnees[i]->SetDestination(selection.x,selection.y);
                    }
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if(event.motion.state& SDL_BUTTON(SDL_BUTTON_LEFT))
            {
                selectionEnCours=true;
                rectangleSelectionForme.x=positionCliqueInitial.x;
                rectangleSelectionForme.y=positionCliqueInitial.y;
                rectangleSelectionForme.w=event.motion.x-positionCliqueInitial.x;
                rectangleSelectionForme.h=event.motion.y-positionCliqueInitial.y;
                if(rectangleSelectionForme.w<0)
                {
                  rectangleSelectionForme.w=-rectangleSelectionForme.w;
                  rectangleSelectionForme.x-=rectangleSelectionForme.w;
                }
                if(rectangleSelectionForme.h<0)
                {
                  rectangleSelectionForme.h=-rectangleSelectionForme.h;
                    rectangleSelectionForme.y-=rectangleSelectionForme.h;
                }
                CreerTextureRectangleSelection();
                TesterIntersectionAvecJoueur();
            }
                        break;

        case SDL_MOUSEBUTTONUP:
                selectionEnCours=false;
            break;
    }

}

void PlayerController::CreerTextureRectangleSelection()
{
    SDL_Surface *rectangleSelectionSurface =SDL_CreateRGBSurface(0,rectangleSelectionForme.w,rectangleSelectionForme.h,32,0,0,0,0);

    SDL_FillRect(rectangleSelectionSurface,NULL,SDL_MapRGB(rectangleSelectionSurface->format,255,0,0));
    SDL_SetColorKey(rectangleSelectionSurface,SDL_TRUE,SDL_MapRGB(rectangleSelectionSurface->format,255,0,0));

    SDL_Rect ligneHaut;
    ligneHaut.x=0;
    ligneHaut.y=0;
    ligneHaut.h=1;
    ligneHaut.w=rectangleSelectionForme.w;
    SDL_FillRect(rectangleSelectionSurface,&ligneHaut,SDL_MapRGB(rectangleSelectionSurface->format,0,255,0));

    SDL_Rect ligneBas;
    ligneBas.x=0;
    ligneBas.y=rectangleSelectionForme.h-1;
    ligneBas.h=1;
    ligneBas.w=rectangleSelectionForme.w;
    SDL_FillRect(rectangleSelectionSurface,&ligneBas,SDL_MapRGB(rectangleSelectionSurface->format,0,255,0));

    SDL_Rect ligneGauche;
    ligneGauche.x=0;
    ligneGauche.y=0;
    ligneGauche.h=rectangleSelectionForme.h;
    ligneGauche.w=1;
    SDL_FillRect(rectangleSelectionSurface,&ligneGauche,SDL_MapRGB(rectangleSelectionSurface->format,0,255,0));

    SDL_Rect ligneDroite;
    ligneDroite.x=rectangleSelectionForme.w-1;
    ligneDroite.y=0;
    ligneDroite.h=rectangleSelectionForme.h;
    ligneDroite.w=1;
    SDL_FillRect(rectangleSelectionSurface,&ligneDroite,SDL_MapRGB(rectangleSelectionSurface->format,0,255,0));



    selectionTexture=SDL_CreateTextureFromSurface(renderer,rectangleSelectionSurface);
    SDL_FreeSurface(rectangleSelectionSurface);

}
void PlayerController::TesterIntersectionAvecJoueur()
{
    unitesSelectionnees.clear();
    for(unsigned int i=0;i<unitesJoueur.size();i++)
    {
        if(unitesJoueur[i]->EstDansRectangleSelection(rectangleSelectionForme))
        {
            unitesSelectionnees.push_back(unitesJoueur[i]);
        }
    }
}

void PlayerController::Render()
{
    if(selectionEnCours)
    {
        SDL_RenderCopy(renderer,selectionTexture,NULL,&rectangleSelectionForme);
    }
}

