#include "Library.h"

// menu graphique pour l'étude des flots (4.6 du CDC)
void menuFlot (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho)
{
    // Variable exit condition
    int exit_condition = 0;

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    VectorName.push_back("flot max chem"); // pour question 4.6
    VectorName.push_back("flot max ecart"); // pour question 4.6
    VectorName.push_back("Modif Val flot"); // option en plus

    //Button Exit condition
    Button exitButton (0);
    int posButtonExit_X = 20,posButtonExit_Y = 20;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    //Button Accept condition
    Button acceptButton (5);
    int posButtonAccept_X = (SCREEN_W - 120)/2,posButtonAccept_Y = 520;
    int buttonAccept_condition = 0;
    int sound_ConditionAccept = 1;
    bool ExitResponseAccept = false;

    //Condition for selection
    std::deque <bool> VectorCondition;

    for (unsigned int I=0; I < VectorName.size(); I++)
    {
        VectorCondition.push_back(false);
    }

    int NombreDeNom = 0;

    NombreDeNom = VectorName.size();

    //Buffercard Dimention

    int BuffCard_W = 444;
    int BuffCard_H =  5+ 67*NombreDeNom + ( NombreDeNom-1)* 8  +10;

    //Buffer et condition d'affichage

    int textAvancement = 0;
    char BuffChar = '0';

    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
                               // un choix, le choix dans le swich tout en bas se dirige vers l'option "default


    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,402 - 90);
    clear_bitmap(BufWindow);


    while (exit_condition == 0)
    {
        blit(Ima2.TODO[39],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"SELECTIONNER UNE FONCTIONALITE:");

        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }


        //Afficher les noms des fonctionnalité possible
        clear_bitmap(BufWindow);
        rectfill (BufWindow,0,0,BufWindow->w,BufWindow->h,makeacol(255,0,255,255));
        clear_bitmap(BufferCard);
        rectfill (BufferCard,0,0,BufferCard->w,BufferCard->h,makeacol(255,0,255,255));


        if (VectorName.size() != 0)
        {
            // BuffAffiche = 0;
            for (int I=0; I< NombreDeNom; I++)
            {
                draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                textAvancement = 15;

                for (unsigned int J =0; J< VectorName[I].size(); J++)
                {
                    BuffChar = VectorName[I][J];

                    if (BuffChar>= 97)
                    {
                        BuffChar = BuffChar - 32;
                    }

                    if (BuffChar == 32)
                    {
                        textAvancement = textAvancement + 15;
                    }

                    if(BuffChar != 32)
                    {
                        draw_sprite(BufferCard,Ima2.TODO[BuffChar  - 65 + 11],textAvancement,5+ I*67 +(I-1)*8 + 15  + 14);
                        textAvancement+= Ima2.TODO[BuffChar  - 65 + 11]->w;
                    }

                }


                //Condition pour cliquer sur l'option qu'on veut
                if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                {
                    if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ I*67 +(I-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 30 )&&(mouse_y < 5+ I*67 +(I-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 30)&&(mouse_b&1))
                    {
                        for (unsigned int J =0; J< VectorName.size(); J++)
                        {
                            VectorCondition[J] = false;
                        }
                        VectorCondition[I] = true;
                    }
                }

                if (VectorCondition[I] == true)
                {
                    draw_sprite (BufferCard,Ima2.TODO[38],10,5+ I*67 +(I-1)*8 + 15);

                    BufferChoice = I;
                }
            }
        }

        blit(BufferCard,BufWindow,0,0,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 30 );


        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {
            switch (BufferChoice)
            {
            case 0:
                grapho.etudeFlotMax(Ima2,Samp4,Music);
                break;

            case 1:
                grapho.bufferParcour(Ima2,Samp4,Music,false);
                break;

            case 2:
                grapho.modifValFlot(Ima2,Samp4,Music);
                break;

            default :
                break;
            }


        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);

}
