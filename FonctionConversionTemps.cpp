#include "Library.h"

//Fonction spéciale pour la conversion du temps
int transformerTempsEnSeconde(std::pair<int, int> Tempo)
{
    return ( Tempo.first * 60 + Tempo.second);
}

// fonction pour afficher un temps en seconde sous la forme x heure(s), y minute(s) et z seconde(s)
std::string afficherSecondeEnTemps(int seconde)
{
    std::ostringstream oss;

    int bufferSeconde = seconde%60;

    int  minute = (seconde - bufferSeconde)/60;

    int bufferMinute = minute%60;
    int heure = (minute - bufferMinute)/60;

    oss << heure << "h "<< bufferMinute << "m " << bufferSeconde <<"s";

    return oss.str();
}
