#include "Library.h"

//Sous programme permettant d'effacer de la memoire les images charger au debut du programme
void EraseImages (Images *Ima )
{
    for (int I=0; I < NBimageTodo ; I++)
    {
        destroy_bitmap(Ima->TODO [I]) ;
    }

    delete Ima->TODO;

    destroy_bitmap(Ima->page);
    destroy_bitmap(Ima->BuffpageAvant);
}

