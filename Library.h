#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

///Constantes
#define NBimageTodo 43

///Libraries
#include <iostream>
#include <allegro.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <fstream>
#include <deque>
#include <queue>
#include <map>
#include <algorithm>
#include <set>
#include <stack>


///Structures
struct Images
{
    BITMAP ** TODO;

    BITMAP * page;
    BITMAP * BuffpageAvant;

};


struct samples
{
    SAMPLE* press_button_1;
    SAMPLE* press_button_2;
    SAMPLE* music_fond;
};

struct sound
{
    int volume;
    bool music_on;
};


///Personal library
#include "ButtonClasse.h"
#include "Graphe.h"

class Graphe;

///Sous programmes
// ecran d'accueil de la borne
void EcranAcceuilleBorne (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho);
// chargement des images
void LoadImages (Images * Ima);
// suppression des images
void EraseImages (Images *Ima );
// chargement des sons
void InitSamples (samples *SampStruct);
// suppression des sons
void EraseSample (samples * SampStruct);
// options
void MapAndOptions (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho);
void Settings (Images Ima2, samples  Samp4, sound * Music,BITMAP* BuffPageAvant);

void menu (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho);
void menuFlot (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho);
void menuPreference (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho);

std::string MettreMajuscule(std::string s);

int transformerTempsEnSeconde(std::pair<int, int> Tempo);
std::string afficherSecondeEnTemps(int seconde);


#endif // LIBRARY_H_INCLUDED
