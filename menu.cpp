#include "Library.h"

void menu (Images Ima2, samples  Samp4, sound * Music,Graphe& grapho)
{
    // Variable exit condition
    int exit_condition = 0;

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;
    VectorName.push_back(" Plan station"); // option en plus

    VectorName.push_back(" Info Sommets");    // pour question 4.3
    VectorName.push_back("  Info trajets");   // pour question 4.3
    VectorName.push_back("Chemins trajet");   // pour question 4.4
    VectorName.push_back("Chemins temps");    // pour question 4.4
    VectorName.push_back("Itineraire piste"); // pour question 4.4
    VectorName.push_back("Itineraire temps"); // pour question 4.4
    VectorName.push_back("Chemin perso");     // pour question 4.5
    VectorName.push_back("etude flot max");   // pour question 4.6

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

    //Slider1 condition
    int rect_pos_x_1 = 640;
    int rect_pos_y_1 = (SCREEN_H - 287)/2 - 12;
    int rect_pos_x_2 = rect_pos_x_1 + 16;
    int rect_pos_y_2 = rect_pos_y_1 + 287;
    int slider_taille = 50;
    int rect2_pos_X_1 = rect_pos_x_1 + 1;
    int rect2_pos_Y_1 = rect_pos_y_1 + 1 + 16;
    int rect2_pos_X_2 = rect_pos_x_2 - 1;
    int rect2_pos_Y_2 = rect2_pos_Y_1 + slider_taille;
    int button_color_up = 0;
    int button_color_down = 0;
    int clickCondition = 0;
    int difference = 0;
    int SliderSoundCondition = 0;

    int AvanceSlide = 0;

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
        blit(Ima2.TODO[8],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

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
                    if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ I*67 +(I-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 30 - AvanceSlide)&&(mouse_y < 5+ I*67 +(I-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 30 - AvanceSlide)&&(mouse_b&1))
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

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 30);

        // Slider a droite de l'ecran

        rectfill(Ima2.page,rect_pos_x_1 - 5,rect_pos_y_1 -5,rect_pos_x_2 +5,rect_pos_y_2 +5,makeacol(20,20,20,255));

        rectfill(Ima2.page,rect_pos_x_1,rect_pos_y_1,rect_pos_x_2,rect_pos_y_2,makeacol(190,190,190,255));
        rectfill(Ima2.page,rect2_pos_X_1,rect2_pos_Y_1,rect2_pos_X_2,rect2_pos_Y_2,makeacol(150,150,150,255));

        triangle(Ima2.page,rect_pos_x_1 + (rect_pos_x_2 - rect_pos_x_1) / 2,rect_pos_y_1 + 4,rect_pos_x_1 + 3,rect_pos_y_1 + 10,rect_pos_x_2 - 3,rect_pos_y_1 + 10,makeacol(100 + button_color_up*50,100 + button_color_up*50,100 + button_color_up*50,255));
        triangle(Ima2.page,rect_pos_x_1 + (rect_pos_x_2 - rect_pos_x_1) / 2,rect_pos_y_2 - 4,rect_pos_x_1 + 3,rect_pos_y_2 - 10,rect_pos_x_2 - 3,rect_pos_y_2 - 10,makeacol(100 + button_color_down*50,100 + button_color_down*50,100 + button_color_down*50,255));

        if ((mouse_b&1)&&((mouse_x > rect2_pos_X_1)&&(mouse_x < rect2_pos_X_2))&&((mouse_y > rect2_pos_Y_1)&&(mouse_y < rect2_pos_Y_2)))
        {
            clickCondition = 1;
        }

        if ((clickCondition == 1)&&(mouse_b&1))
        {
            rect2_pos_Y_1 = mouse_y - difference;
            rect2_pos_Y_2 = rect2_pos_Y_1 + slider_taille;
            AvanceSlide =  ((rect2_pos_Y_1 - (rect_pos_y_1 +17)) * (BuffCard_H - BufWindow->h))/(rect_pos_y_2 - 17 - slider_taille- (rect_pos_y_1 +17));
        }
        else
        {
            difference = mouse_y - rect2_pos_Y_1;
        }

        if (!mouse_b&1)
        {
            clickCondition = 0;
        }

        //Blindage slide des cartes

        if (AvanceSlide <= 0)
        {
            AvanceSlide = 0;
        }

        if (AvanceSlide >= BuffCard_H - BufWindow->h)
        {
            AvanceSlide = BuffCard_H - BufWindow->h;
        }

        // Condition pour que le slider ne sorte pas de sa rampe

        if ((rect2_pos_Y_1 <= rect_pos_y_1 +17)||(rect2_pos_Y_2 >= rect_pos_y_2 - 17))
        {
            if (SliderSoundCondition == 1)
            {
                if (Music->music_on == true)
                {
                    play_sample(Samp4.press_button_1,Music->volume,128,1000,0);
                }
                SliderSoundCondition = 0;
            }
        }
        else
        {
            SliderSoundCondition = 1;
        }

        if (rect2_pos_Y_1 <= rect_pos_y_1 +17)
        {

            rect2_pos_Y_1 = rect_pos_y_1 +17;
            rect2_pos_Y_2 = rect2_pos_Y_1 + slider_taille;
            button_color_up = 1;
        }
        else
        {
            button_color_up = 0;
        }

        if (rect2_pos_Y_2 >= rect_pos_y_2 - 17)
        {

            rect2_pos_Y_2 = rect_pos_y_2 - 17;
            rect2_pos_Y_1 = rect2_pos_Y_2 - slider_taille;
            button_color_down = 1;
        }
        else
        {
            button_color_down = 0;
        }

        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {
            switch (BufferChoice)
            {
            case 0:
                MapAndOptions(Ima2,Samp4,Music,grapho);
                break;

            case 1:
                grapho.choixSommet(Ima2,Samp4,Music);
                break;

            case 2:
                grapho.choixTrajet(Ima2,Samp4,Music);
                break;

            case 3:
                grapho.BFS(Ima2,Samp4,Music);
                break;

            case 4:
                grapho.dijkstraTemps(Ima2,Samp4,Music,false);
                break;

            case 5:
                grapho.BFS2(Ima2,Samp4,Music);
                break;

            case 6:
                 grapho.dijkstraTemps(Ima2,Samp4,Music,true);
                break;

             case 7:
                 menuPreference(Ima2,Samp4,Music,grapho);
                break;

            case 8:
                menuFlot(Ima2,Samp4,Music,grapho);
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
