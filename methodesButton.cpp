#include "Library.h"

//Sous-programme de la classe "Button"

// constructeur par defaut de la classe Bouton
Button::Button()
    : m_image (NULL),m_buttontype (0), m_samp_sound1(0), m_samp_sound2(0)
{

}

// constructeur surchargé de la classe bouton
Button::Button (int ButtonType)
    : m_image (NULL),m_buttontype (ButtonType)
{
    char BufferNomImage [50] = "";

    switch (ButtonType)
    {
    case 0:
        strcpy(BufferNomImage,"Buttons/buttonFlecheGauche.bmp") ;
        break;

    case 1:
        strcpy(BufferNomImage,"Buttons/buttonListe.bmp") ;
        break;

    case 2:
        strcpy(BufferNomImage,"Buttons/buttonCroix.bmp") ;
        break;

     case 3:
        strcpy(BufferNomImage,"Buttons/buttonPetitPlus.bmp") ;
        break;

     case 4:
        strcpy(BufferNomImage,"Buttons/buttonPetitMoins.bmp") ;
        break;

    case 5:
        strcpy(BufferNomImage,"Buttons/buttonAccept.bmp") ;
        break;

    case 6:
        strcpy(BufferNomImage,"Buttons/buttonSettings.bmp") ;
        break;

    case 7:
        strcpy(BufferNomImage,"Buttons/buttonMusicOn.bmp") ;
        break;

    case 8:
        strcpy(BufferNomImage,"Buttons/buttonMusicOff.bmp") ;
        break;

    case 9:
        strcpy(BufferNomImage,"Buttons/buttonEnter.bmp") ;
        break;

    }

    m_image = load_bitmap(BufferNomImage, NULL);
    if (!m_image)
    {
        allegro_message("Error loading : image  button type : %d",m_buttontype);
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    //Init sample
    m_samp_sound1 = load_sample("Samples/press_button_1.wav");

    if(!m_samp_sound1)
    {
        allegro_message("problem sample press_button_1");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    m_samp_sound2 = load_sample("Samples/press_button_2.wav");

    if(!m_samp_sound2)
    {
        allegro_message("problem sample press_button_2");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

// destructeur de la classe Bouton
Button::~Button()
{
    if (m_image != NULL)
    {
        destroy_bitmap(m_image);
    }

    destroy_sample(m_samp_sound1);
    destroy_sample(m_samp_sound2);
}



bool Button::activerButton(int posButton_X,int posButton_Y,BITMAP * page, int *  button_condition, int * sound_Condition,sound * Music)
{
    //Polygon for shadow of the EXIT button
    int polygon_tab[20];

    switch (m_buttontype)
    {
    case 0:
        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 64;
        polygon_tab[2] = posButton_X + 13;
        polygon_tab[3] = posButton_Y + 77;
        polygon_tab[4] = posButton_X + 17;
        polygon_tab[5] = posButton_Y+ 74;
        polygon_tab[6] = posButton_X+ 60;
        polygon_tab[7] = posButton_Y + 74;
        polygon_tab[8] = posButton_X+ 63;
        polygon_tab[9] = posButton_Y + 77;
        polygon_tab[10] = posButton_X + 77;
        polygon_tab[11] = posButton_Y + 63;
        polygon_tab[12] = posButton_X + 74;
        polygon_tab[13] = posButton_Y + 60;
        polygon_tab[14] = posButton_X+ 74;
        polygon_tab[15] = posButton_Y+ 17;
        polygon_tab[16] = posButton_X + 77;
        polygon_tab[17] = posButton_Y+ 12;
        polygon_tab[18] = posButton_X + 64;
        polygon_tab[19] = posButton_Y;
        break;


    case 1:
        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 64;
        polygon_tab[2] = posButton_X + 13;
        polygon_tab[3] = posButton_Y + 77;
        polygon_tab[4] = posButton_X + 17;
        polygon_tab[5] = posButton_Y+ 74;
        polygon_tab[6] = posButton_X+ 60;
        polygon_tab[7] = posButton_Y + 74;
        polygon_tab[8] = posButton_X+ 63;
        polygon_tab[9] = posButton_Y + 77;
        polygon_tab[10] = posButton_X + 77;
        polygon_tab[11] = posButton_Y + 63;
        polygon_tab[12] = posButton_X + 74;
        polygon_tab[13] = posButton_Y + 60;
        polygon_tab[14] = posButton_X+ 74;
        polygon_tab[15] = posButton_Y+ 17;
        polygon_tab[16] = posButton_X + 77;
        polygon_tab[17] = posButton_Y+ 12;
        polygon_tab[18] = posButton_X + 64;
        polygon_tab[19] = posButton_Y;
        break;


    case 3:
        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 64;
        polygon_tab[2] = posButton_X + 13;
        polygon_tab[3] = posButton_Y + 77;
        polygon_tab[4] = posButton_X + 17;
        polygon_tab[5] = posButton_Y+ 74;
        polygon_tab[6] = posButton_X+ 60;
        polygon_tab[7] = posButton_Y + 74;
        polygon_tab[8] = posButton_X+ 63;
        polygon_tab[9] = posButton_Y + 77;
        polygon_tab[10] = posButton_X + 77;
        polygon_tab[11] = posButton_Y + 63;
        polygon_tab[12] = posButton_X + 74;
        polygon_tab[13] = posButton_Y + 60;
        polygon_tab[14] = posButton_X+ 74;
        polygon_tab[15] = posButton_Y+ 17;
        polygon_tab[16] = posButton_X + 77;
        polygon_tab[17] = posButton_Y+ 12;
        polygon_tab[18] = posButton_X + 64;
        polygon_tab[19] = posButton_Y;
        break;


    case 4:
        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 106;
        polygon_tab[2] = posButton_X + 23;
        polygon_tab[3] = posButton_Y + 127;
        polygon_tab[4] = posButton_X + 29;
        polygon_tab[5] = posButton_Y+ 122;
        polygon_tab[6] = posButton_X+ 216;
        polygon_tab[7] = posButton_Y + 122;
        polygon_tab[8] = posButton_X+ 222;
        polygon_tab[9] = posButton_Y + 127;
        polygon_tab[10] = posButton_X + 245;
        polygon_tab[11] = posButton_Y + 105;
        polygon_tab[12] = posButton_X + 239;
        polygon_tab[13] = posButton_Y + 99;
        polygon_tab[14] = posButton_X+ 239;
        polygon_tab[15] = posButton_Y+ 27;
        polygon_tab[16] = posButton_X + 244;
        polygon_tab[17] = posButton_Y+ 21;
        polygon_tab[18] = posButton_X + 223;
        polygon_tab[19] = posButton_Y;
        break;

    case 5:

        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 51;
        polygon_tab[2] = posButton_X + 11;
        polygon_tab[3] = posButton_Y + 62;
        polygon_tab[4] = posButton_X + 13;
        polygon_tab[5] = posButton_Y+ 59;
        polygon_tab[6] = posButton_X+ 104;
        polygon_tab[7] = posButton_Y + 59;
        polygon_tab[8] = posButton_X+ 107;
        polygon_tab[9] = posButton_Y + 62;
        polygon_tab[10] = posButton_X + 118;
        polygon_tab[11] = posButton_Y + 51;
        polygon_tab[12] = posButton_X + 115;
        polygon_tab[13] = posButton_Y + 49;
        polygon_tab[14] = posButton_X+ 115;
        polygon_tab[15] = posButton_Y+ 13;
        polygon_tab[16] = posButton_X + 118;
        polygon_tab[17] = posButton_Y+ 10;
        polygon_tab[18] = posButton_X + 106;
        polygon_tab[19] = posButton_Y;
        break;


    case 15:

        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 51;
        polygon_tab[2] = posButton_X + 11;
        polygon_tab[3] = posButton_Y + 62;
        polygon_tab[4] = posButton_X + 13;
        polygon_tab[5] = posButton_Y+ 59;
        polygon_tab[6] = posButton_X+ 104;
        polygon_tab[7] = posButton_Y + 59;
        polygon_tab[8] = posButton_X+ 107;
        polygon_tab[9] = posButton_Y + 62;
        polygon_tab[10] = posButton_X + 118;
        polygon_tab[11] = posButton_Y + 51;
        polygon_tab[12] = posButton_X + 115;
        polygon_tab[13] = posButton_Y + 49;
        polygon_tab[14] = posButton_X+ 115;
        polygon_tab[15] = posButton_Y+ 13;
        polygon_tab[16] = posButton_X + 118;
        polygon_tab[17] = posButton_Y+ 10;
        polygon_tab[18] = posButton_X + 106;
        polygon_tab[19] = posButton_Y;
        break;

    case 16:

        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 51;
        polygon_tab[2] = posButton_X + 11;
        polygon_tab[3] = posButton_Y + 62;
        polygon_tab[4] = posButton_X + 13;
        polygon_tab[5] = posButton_Y+ 59;
        polygon_tab[6] = posButton_X+ 104;
        polygon_tab[7] = posButton_Y + 59;
        polygon_tab[8] = posButton_X+ 107;
        polygon_tab[9] = posButton_Y + 62;
        polygon_tab[10] = posButton_X + 118;
        polygon_tab[11] = posButton_Y + 51;
        polygon_tab[12] = posButton_X + 115;
        polygon_tab[13] = posButton_Y + 49;
        polygon_tab[14] = posButton_X+ 115;
        polygon_tab[15] = posButton_Y+ 13;
        polygon_tab[16] = posButton_X + 118;
        polygon_tab[17] = posButton_Y+ 10;
        polygon_tab[18] = posButton_X + 106;
        polygon_tab[19] = posButton_Y;
        break;

    case 17:

        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 51;
        polygon_tab[2] = posButton_X + 11;
        polygon_tab[3] = posButton_Y + 62;
        polygon_tab[4] = posButton_X + 13;
        polygon_tab[5] = posButton_Y+ 59;
        polygon_tab[6] = posButton_X+ 104;
        polygon_tab[7] = posButton_Y + 59;
        polygon_tab[8] = posButton_X+ 107;
        polygon_tab[9] = posButton_Y + 62;
        polygon_tab[10] = posButton_X + 118;
        polygon_tab[11] = posButton_Y + 51;
        polygon_tab[12] = posButton_X + 115;
        polygon_tab[13] = posButton_Y + 49;
        polygon_tab[14] = posButton_X+ 115;
        polygon_tab[15] = posButton_Y+ 13;
        polygon_tab[16] = posButton_X + 118;
        polygon_tab[17] = posButton_Y+ 10;
        polygon_tab[18] = posButton_X + 106;
        polygon_tab[19] = posButton_Y;
        break;
    }

    if ((m_buttontype>=6)&&(m_buttontype<=10))
    {
        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 75;
        polygon_tab[2] = posButton_X + 16;
        polygon_tab[3] = posButton_Y + 92;
        polygon_tab[4] = posButton_X + 20;
        polygon_tab[5] = posButton_Y+ 88;
        polygon_tab[6] = posButton_X+ 156;
        polygon_tab[7] = posButton_Y + 88;
        polygon_tab[8] = posButton_X+ 161;
        polygon_tab[9] = posButton_Y + 92;
        polygon_tab[10] = posButton_X + 176;
        polygon_tab[11] = posButton_Y + 76;
        polygon_tab[12] = posButton_X + 173;
        polygon_tab[13] = posButton_Y + 71;
        polygon_tab[14] = posButton_X+ 173;
        polygon_tab[15] = posButton_Y+ 19;
        polygon_tab[16] = posButton_X + 177;
        polygon_tab[17] = posButton_Y+ 15;
        polygon_tab[18] = posButton_X + 159;
        polygon_tab[19] = posButton_Y;

    }

    if ((m_buttontype==6)||(m_buttontype==7)||(m_buttontype==8))
    {

        polygon_tab[0] = posButton_X;
        polygon_tab[1] = posButton_Y+ 64;
        polygon_tab[2] = posButton_X + 13;
        polygon_tab[3] = posButton_Y + 77;
        polygon_tab[4] = posButton_X + 17;
        polygon_tab[5] = posButton_Y+ 74;
        polygon_tab[6] = posButton_X+ 60;
        polygon_tab[7] = posButton_Y + 74;
        polygon_tab[8] = posButton_X+ 63;
        polygon_tab[9] = posButton_Y + 77;
        polygon_tab[10] = posButton_X + 77;
        polygon_tab[11] = posButton_Y + 63;
        polygon_tab[12] = posButton_X + 74;
        polygon_tab[13] = posButton_Y + 60;
        polygon_tab[14] = posButton_X+ 74;
        polygon_tab[15] = posButton_Y+ 17;
        polygon_tab[16] = posButton_X + 77;
        polygon_tab[17] = posButton_Y+ 12;
        polygon_tab[18] = posButton_X + 64;
        polygon_tab[19] = posButton_Y;
    }

    bool ConditionActivate = false;

    // button
    // verify if the mouse is on the settings button
    if ((mouse_x > posButton_X - 3) && (mouse_x < posButton_X - 3 + m_image->w ) && (mouse_y > posButton_Y - 3) && (mouse_y < posButton_Y - 3 + m_image->h) && (mouse_b&1))
    {
        // draw the button on its click-position
        draw_sprite (page,m_image,posButton_X,posButton_Y );

        // set the settings condition
        *button_condition = 1;

        if((*sound_Condition == 1) && (Music->music_on == true))
        {
            play_sample(m_samp_sound1,Music->volume,128,1000,0);
            *sound_Condition = 0;
        }
    }
    // verify if we left-click on the mouse
    else if (!mouse_b&1)
    {
        // if its on the button it launches the settings page
        if (*button_condition == 1)
        {
            if( Music->music_on == true)
            {
                *sound_Condition = 1;
                play_sample(m_samp_sound2,Music->volume,128,1000,0);
            }

            ConditionActivate = true;
            *button_condition = 0;
        }

        // draw the shadow which has been created
        polygon(page, 10, polygon_tab, makeacol(87, 46, 28, 125));
        // draw the settings button
        draw_sprite (page,m_image,posButton_X - 3,posButton_Y - 3);
    }

    // we don't left-click and we aren't on the button
    else
    {
        // set the condition
        *button_condition = 0;
        *sound_Condition = 1;
        // draw the shadow which has been created
        polygon(page, 10, polygon_tab, makeacol(87, 46, 28, 125));
        // draw the settings button
        draw_sprite (page,m_image,posButton_X - 3,posButton_Y - 3);
    }
    return ConditionActivate;
}

bool Button::activerButtonCercle(int posButton_X,int posButton_Y,BITMAP * page, int *  button_condition, int * sound_Condition,sound * Music)
{

    // Button activation parameters
    int RadiusSquare = 0;

    int Rayon = 0;

    switch (m_buttontype)
    {
    case 2:
        Rayon = 28;
        break;
    }

    bool ConditionActivate = false;

    //Button activation part
    RadiusSquare = ( posButton_X+ m_image->w/ 2 - mouse_x) * ( posButton_X + m_image->w/ 2 - mouse_x)+ ( posButton_Y + m_image->h / 2 - mouse_y) * (posButton_Y + m_image->h / 2 - mouse_y) ;
    if ((RadiusSquare < Rayon*Rayon) && (mouse_b&1))
    {

        draw_sprite (page,m_image,posButton_X,posButton_Y);
        *button_condition = 1;

        if((*sound_Condition== 1) && (Music->music_on == true))
        {

            play_sample(m_samp_sound1,Music->volume,128,1000,0);
            *sound_Condition = 0;
        }
    }

    // verify if we left-click on the mouse
    else if (!mouse_b&1)
    {
        // if the mouse is on the exit button it will exit from the infinit loop
        if ( *button_condition == 1)
        {
            if(Music->music_on == true)
            {
                play_sample(m_samp_sound2,Music->volume,128,1000,0);
                *sound_Condition = 1;
            }

            ConditionActivate = true;
            *button_condition = 0;
        }
        circlefill(page, posButton_X + (m_image->w)/2, posButton_Y + (m_image->h)/2, Rayon, makeacol(87, 46, 28, 125));
        draw_sprite (page,m_image,posButton_X - 2,posButton_Y - 2);
    }
    // we don't left-click and we aren't on a button
    else
    {
        // put variables as default
        *button_condition = 0;
        *sound_Condition = 1;

        // draw the buttons on their normal position
        circlefill(page, posButton_X + (m_image->w)/2, posButton_Y + (m_image->h)/2, Rayon, makeacol(87, 46, 28, 125));
        draw_sprite (page,m_image,posButton_X - 2,posButton_Y - 2);
    }
    return ConditionActivate;
}
