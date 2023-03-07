#include "Library.h"

//Sous programme permettant de charger toutes les images de decors necessaire dans la strucure " Ima "
void LoadImages (Images * Ima)
{

    char buffer  [50] = "";

    //Creer buffer screen commun
    Ima->page = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(Ima->page);

    //Creer buffer screen commun
    Ima->BuffpageAvant= create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(Ima->BuffpageAvant);

    // Charge les images du dossier "images"
    Ima->TODO = new BITMAP*;

    for (int I=0; I< NBimageTodo; I++)
    {
        std::ostringstream oss;
        oss << "images/image" << I << ".bmp";

        for (unsigned int J = 0; J<oss.str().size(); J++)
        {
            buffer[J] = oss.str()[J];
        }


        buffer[oss.str().size()] = '\0';

        Ima->TODO[I] = load_bitmap(buffer, NULL);
        if (!Ima->TODO[I])
        {
            allegro_message("Error loading : image projet %d",I);
            allegro_exit();
            exit(EXIT_FAILURE);
        }
    }
}
