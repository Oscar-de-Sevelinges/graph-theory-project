#include "Library.h"

//Sous programme permettant d'affacer de la memoire les sons et musique charger au debut du programme
void EraseSample (samples * SampStruct)
{
    destroy_sample(SampStruct->press_button_1);
    destroy_sample(SampStruct->press_button_2);
}
