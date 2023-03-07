#ifndef BUTTONCLASSE_H_INCLUDED
#define BUTTONCLASSE_H_INCLUDED


///Personal library
#include "Library.h"


///Classe


class Button
{
private:

    BITMAP * m_image;
    int m_buttontype;
    SAMPLE * m_samp_sound1;
    SAMPLE * m_samp_sound2;


public:

    //Constructeur
    Button();
    Button(int ButtonType);


    //Destructeur
    ~Button();

    //Methodes

    bool activerButton (int posButton_X,int posButton_Y,BITMAP * page, int *  button_condition, int * sound_Condition,sound * Music) ;
    bool activerButtonCercle (int posButton_X,int posButton_Y,BITMAP * page, int *  button_condition, int * sound_Condition,sound * Music) ;

};

#endif // BUTTONCLASSE_H_INCLUDED
