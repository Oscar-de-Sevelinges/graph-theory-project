#include "Library.h"

//Permet de charger tout les son dans la structure de type "samples"
void InitSamples (samples *SampStruct)
{

    SampStruct->press_button_1 = NULL;
    SampStruct->press_button_1 = load_sample("samples/press_button_1.wav");

    if(!SampStruct->press_button_1)
    {
        allegro_message("problem sample pour button 1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    SampStruct->press_button_2 = NULL;
    SampStruct->press_button_2 = load_sample("samples/press_button_2.wav");

    if(!SampStruct->press_button_2)
    {
        allegro_message("problem sample pour button 2");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}
