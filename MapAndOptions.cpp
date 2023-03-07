#include "Library.h"

void MapAndOptions (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho)
{
    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (0);
    int posButtonExit_X = 20,posButtonExit_Y = 20;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[1],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }
        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}
