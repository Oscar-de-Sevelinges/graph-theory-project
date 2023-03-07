#include "Library.h"

void EcranAcceuilleBorne (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho)
{

    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (2);
    int posButtonExit_X = 737,posButtonExit_Y = 13;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    //Button Enter condition
    Button enterButton (9);
    int posButtonEnter_X = 570,posButtonEnter_Y = 472;
    int buttonEnter_condition = 0;
    int sound_ConditionEnter = 1;
    bool EnterResponse = false;

    //Button Settings condition
    Button settingsButton (6);
    int posButtonSettings_X = 20,posButtonSettings_Y = 20;
    int buttonSettings_condition = 0;
    int sound_ConditionSettings= 1;
    bool ExitResponseSettings = false;



     while (exit_condition == 0)
    {
        blit(Ima2.TODO[0],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);


        ExitResponse = exitButton.activerButtonCercle(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        EnterResponse = enterButton.activerButton(posButtonEnter_X,posButtonEnter_Y,Ima2.page,&buttonEnter_condition,&sound_ConditionEnter,Music);
        if ( EnterResponse == true )
        {
            menu(Ima2,Samp4,Music,grapho);
        }

        //Button settings
        ExitResponseSettings = settingsButton.activerButton(posButtonSettings_X,posButtonSettings_Y,Ima2.page,&buttonSettings_condition,&sound_ConditionSettings,Music);
        if ( ExitResponseSettings == true )
        {
            Settings(Ima2,Samp4,Music,Ima2.BuffpageAvant);

        }
        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);
    }

}
