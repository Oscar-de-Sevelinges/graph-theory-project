#include "Library.h"

//Sous programme affichant les sttings de son du jeu, permettant ainsi de regler le son

void Settings (Images Ima2, samples  Samp4, sound * Music,BITMAP* BuffPageAvant)
{
    int Exit_condition = 0;

    int PosPanneau_X = (SCREEN_W - Ima2.TODO[3]->w)/2;
    int PosPanneau_Y =  -Ima2.TODO[3]->h - 1;

    int ActionPanneau = 0;

    //Button Exit condition
    Button exitButton (2);
    int posButtonExit_X = 520,posButtonExit_Y = 150;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    //Button Music On condition
    Button musicOnButton (7);
    int posButtonMusicOn_X = PosPanneau_X + (Ima2.TODO[3]->w - 80)/2,posButtonMusicOn_Y = PosPanneau_Y + 57;
    int buttonMusicOn_condition = 0;
    int sound_ConditionMusicOn = 1;
    bool ExitResponseMusicOn = false;

    //Button Music Off condition
    Button musicOffButton (8);
    int buttonMusicOff_condition = 0;
    int sound_ConditionMusicOff = 1;
    bool ExitResponseMusicOff = false;

    //Partie pour les boutons pour augmenter ou diminuer le volume sonore
    int RadiusSquare = 0;

    BITMAP * BuffVolumeBarre = NULL;
    BuffVolumeBarre = create_bitmap((Ima2.TODO[4]->w)/2,Ima2.TODO[4]->h);
    clear_bitmap(BuffVolumeBarre);

    int buttonPlus_X = PosPanneau_X + (Ima2.TODO[3]->w - BuffVolumeBarre->w)/2 + BuffVolumeBarre->w - 10;
    int buttonPlus_Y = PosPanneau_Y + 150;
    int buttonMoins_X = PosPanneau_X + (Ima2.TODO[3]->w - BuffVolumeBarre->w)/2  - 4;
    int buttonMoins_Y = PosPanneau_Y + 150;

    int RayonPlusMoins = 13;

    int buttonPlus_condition = 0;
    int SoundCondition_Plus = 1;

    int buttonMoins_condition = 0;
    int SoundCondition_Moins = 1;

    while (Exit_condition == 0)
    {
        blit(BuffPageAvant,Ima2.page,0,0,0,0,SCREEN_W, SCREEN_H);
        //Mettre une ombre sur l'ecran arrière
        rectfill (Ima2.page,0,0,SCREEN_W,SCREEN_H,makeacol(0,0,0,150));

        draw_sprite (Ima2.page,Ima2.TODO[3],PosPanneau_X,PosPanneau_Y);
        textprintf_centre_ex(Ima2.page,font,PosPanneau_X + (Ima2.TODO[3]->w)/2,PosPanneau_Y + 30,makecol(255,255,255),-1,"VOLUME :");
        textprintf_centre_ex(Ima2.page,font,PosPanneau_X + (Ima2.TODO[3]->w)/2 - 2,PosPanneau_Y + 42,makecol(255,255,255),-1,"****************");

        if (Music->music_on == true)
        {
            ExitResponseMusicOn = musicOnButton.activerButton(posButtonMusicOn_X,posButtonMusicOn_Y,Ima2.page,&buttonMusicOn_condition,&sound_ConditionMusicOn,Music);

            if ( ExitResponseMusicOn == true )
            {
                if (ActionPanneau == 1)
                {
                    Music->music_on = false;

                    // Music->volume = 0;

                    stop_sample(Samp4.music_fond);
                }
            }
        }
        else
        {
            ExitResponseMusicOff = musicOffButton.activerButton(posButtonMusicOn_X,posButtonMusicOn_Y,Ima2.page,&buttonMusicOff_condition,&sound_ConditionMusicOff,Music);
            if ( ExitResponseMusicOff == true )
            {
                if (ActionPanneau == 1)
                {
                    Music->music_on = true;

                    Music->volume = 255;
                }
            }
        }

        if ((Music->volume != 0)&&(Music->music_on == true))
        {
            //affichage Valume Barre
            clear_bitmap(BuffVolumeBarre);

            blit(Ima2.TODO[4],BuffVolumeBarre,255*0.6 - Music->volume*0.6,0,0,0,BuffVolumeBarre->w,BuffVolumeBarre->h);
            draw_sprite(Ima2.page,BuffVolumeBarre,PosPanneau_X + (Ima2.TODO[3]->w - BuffVolumeBarre->w)/2,PosPanneau_Y + 150);

            //Affichage button plus volume

            RadiusSquare = ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) * (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {

                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X,buttonPlus_Y );
                buttonPlus_condition = 1;

                Music->volume = Music->volume + 1;

                if((SoundCondition_Plus == 1) && (Music->music_on == true))
                {

                    SoundCondition_Plus = 0;
                }
            }

            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonPlus_condition == 1)
                {
                    if(Music->music_on == true)
                    {
                        SoundCondition_Plus= 1;
                    }
                    buttonPlus_condition  = 0;
                }
                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);
            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonPlus_condition = 0;
                SoundCondition_Plus = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);
            }

            //Affichage button moins volume

            RadiusSquare = ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ (buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) * (buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X,buttonMoins_Y );
                buttonMoins_condition = 1;

                Music->volume = Music->volume - 1;

                if((SoundCondition_Moins == 1) && (Music->music_on == true))
                {

                    SoundCondition_Moins = 0;
                }
            }

            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonMoins_condition == 1)
                {
                    if(Music->music_on == true)
                    {
                        SoundCondition_Moins = 1;
                    }
                    buttonMoins_condition  = 0;
                }

                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);
            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonMoins_condition = 0;
                SoundCondition_Moins = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);
            }

            if (Music->volume <= 0)
            {
                Music->music_on = false;

                stop_sample(Samp4.music_fond);

                Music->volume = 255;
            }

            if (Music->volume >= 255)
            {
                Music->volume = 255;
            }
        }

        set_volume(Music->volume,Music->volume);

        if (ActionPanneau == 0)
        {
            if (PosPanneau_Y != ((SCREEN_H -Ima2.TODO[3]->h )/2))
            {
                PosPanneau_Y++;

                posButtonMusicOn_Y ++;

                buttonPlus_Y ++;
                buttonMoins_Y ++;
            }
            else
            {
                ActionPanneau = 1;
            }
        }

        if (ActionPanneau == 1)
        {

            //Partie gerant le bouton "Exit", simplifier avec la classe button
            ExitResponse = exitButton.activerButtonCercle(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
            if ( ExitResponse == true )
            {
                ActionPanneau = 2;
            }
        }

        if (ActionPanneau == 2)
        {
            if(PosPanneau_Y !=  -Ima2.TODO[3]->h - 10)
            {
                PosPanneau_Y--;
                posButtonMusicOn_Y --;

                buttonPlus_Y --;
                buttonMoins_Y --;
            }
            else
            {
                Exit_condition = 1;
            }
        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

    destroy_bitmap(BuffVolumeBarre);

}
