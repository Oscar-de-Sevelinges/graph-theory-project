
#include "Graphe.h"

// constructeur de la classe Graphe basé sur un fichier texte
Graphe::Graphe(const std::string& nomFichier, bool GrapheEcart)
{
    int Buffer = 0;

    std::ifstream ifs{nomFichier};

    std::ifstream ifs2{"dataUser.txt"};

    if (!ifs)
    {
        // interruption du programme si l'ouverture échoue
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );
    }

    // on récupère l'ordre du graphe
    int ordre;
    ifs >> ordre;
    if (ifs.fail())
    {
        // interruption du programme si l'ouverture échoue
        throw std::runtime_error( "Impossible de lire l'ordre du graphe ");
    }
    // on crée autant de sommet que la valeur de l'ordre
    for(int i = 0; i < ordre; i++)
    {
        std::string nom;
        int altitude;
        ifs >> i >> nom >> altitude;
        m_tabSommets.push_back(new Sommet{i, nom, altitude});
    }

//************************************************************************
    //Zone pour récupérer les datas rajouter
    if (!ifs2)
    {
        // interruption du programme si l'ouverture échoue
        throw std::runtime_error( "Impossible d'ouvrir en lecture fichie data");
    }

    //Data remonté

    for (int I=0; I< 12 ; I++)
    {
        if ((I>=0)&&(I<=4))
        {
            Buffer = nbInfo+1;
        }
        else
        {
            Buffer = nbInfo;
        }

        for (int J=0; J< Buffer ; J++)
        {
            switch (I)
            {

            case 0 :
                ifs2 >> m_data.TPH_info[J];
                //std::cout << m_data.TPH_info[J] << " ";
                break;

            case 1 :
                ifs2 >> m_data.TC_info[J];
                // std::cout << m_data.TC_info[J] << " ";
                break;

            case 2 :
                ifs2 >> m_data.TSD_info[J];
                // std::cout << m_data.TSD_info[J] << " ";

                break;

            case 3 :
                ifs2 >> m_data.TS_info[J];
                // std::cout << m_data.TS_info[J] << " ";
                break;

            case 4 :
                ifs2 >> m_data.TK_info[J];
                // std::cout << m_data.TK_info[J] << " ";
                break;

            case 5 :
                ifs2 >> m_data.BUS_info[J];
                // std::cout << m_data.BUS_info[J] << " ";
                break;

            case 6 :
                ifs2 >> m_data.V_info[J];
                // std::cout << m_data.V_info[J] << " ";
                break;

            case 7 :
                ifs2 >> m_data.B_info[J];
                //  std::cout << m_data.B_info[J] << " ";
                break;

            case 8 :
                ifs2 >> m_data.R_info[J];
                // std::cout << m_data.R_info[J] << " ";
                break;

            case 9 :
                ifs2 >> m_data.N_info[J];
                // std::cout << m_data.N_info[J] << " ";
                break;

            case 10 :
                ifs2 >> m_data.KL_info[J];
                //  std::cout << m_data.KL_info[J] << " ";
                break;

            case 11 :
                ifs2 >> m_data.SURF_info[J];
                // std::cout << m_data.SURF_info[J] << " ";
                break;
            }
        }

        // std::cout << I << std::endl;
    }



//************************************************************************

    // on récupère la taille du graphe
    int taille;
    ifs >> taille;

    // on récupère les infos de chaque arête et on l'ajoute au tableau de trajet du graphe
    for(int i = 0; i < taille; i++)
    {
        std::string nom, type;
        int depart, arrivee;
        ifs >> i >> nom >> type >> depart >> arrivee;
        m_tabTrajets.push_back(new Trajet{i, nom, type, m_tabSommets[depart], m_tabSommets[arrivee],m_data,false});
        m_tabSommets[depart]->setTrajets(m_tabTrajets.back());
        m_tabSommets[arrivee]->setTrajets(m_tabTrajets.back());

        //Partie pour le graphe d'ecart
        if (GrapheEcart == true)
        {
            m_tabTrajets.push_back(new Trajet{(i*(-1))-1, nom, type, m_tabSommets[arrivee], m_tabSommets[depart],m_data,true});
            m_tabSommets[depart]->setTrajets(m_tabTrajets.back());
            m_tabSommets[arrivee]->setTrajets(m_tabTrajets.back());
        }
    }
}

// destructeur de la classe Graphe
Graphe::~Graphe()
{
    int BufferTaille = m_tabSommets.size();

    // on efface chaque sommet du tableau de pointeur de Sommet
    for(int I =0; I < BufferTaille; I++)
    {
        delete m_tabSommets.back();
        m_tabSommets.pop_back();
    }

    BufferTaille = m_tabTrajets.size();
    // on efface chaque trajet du tableau de pointeur de Trajet
    for(int I =0; I < BufferTaille; I++)
    {
        delete m_tabTrajets.back();
        m_tabTrajets.pop_back();
    }
}

// opérateur de sortie pour afficher le graphe
std::ostream &operator<<(std::ostream &os, const Graphe &graphe)
{
    // on affiche le numéro, le nom, l'altitude et le degré de chaque sommet
    std::cout << "Liste des sommets : " << std::endl;

    for(const auto& elem : graphe.getTabSommets())
    {
        std::cout << "Numero du sommet : " << elem->getNum()+1 << "\tNom du sommet : " << elem->getNom() << "\tAltitude du sommet : " << elem->getAltitude() << "\tDegre du sommet : " << elem->getTrajets().size() << std::endl;
    }

    // on affiche le numéro, le nom, le type, les extrémités et le temps de chaque trajet
    std::cout << std::endl << std::endl << "Liste des trajets : " << std::endl;

    for(const auto& elem : graphe.getTabTrajets())
    {
        std::cout << "Numero du trajet : " << elem->getNum()+1 << std::endl;
        std::cout << "Nom du trajet : " << elem->getNom() << std::endl;
        std::cout << "Type de trajet : " << elem->getType() << std::endl;
        std::cout << "Depart du trajet : " << elem->getExtremites().first->getNom() << " Arrivee du trajet : " << elem->getExtremites().second->getNom() << std::endl;
        std::cout << "Temps du trajet : " << elem->getTempsTrajet().first << "m" << elem->getTempsTrajet().second << "sec" << std::endl << std::endl;
    }

    return os;
}

// méthode pour afficher les infos d'un trajet
void Graphe::choixTrajet(Images Ima2, samples  Samp4, sound * Music)  const
{
    // Variable exit condition
    int exit_condition = 0;

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(m_tabTrajets.size()); I++)
    {
        VectorName.push_back(MettreMajuscule(m_tabTrajets[I]->getNom()));
    }

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

    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default


    //Buffercard Dimention

    int BuffCard_W = 444;
    int BuffCard_H =  5+ 67*NombreDeNom + ( NombreDeNom-1)* 8  +10;

    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,380);
    clear_bitmap(BufWindow);

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[39],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);


        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"SUR QUEL TRAJET VOULEZ-VOUS DES INFORMATIONS?");


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
                //draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(0,0,0,255));

                //Condition pour cliquer sur l'option qu'on veut
                if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                {
                    if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ I*67 +(I-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ I*67 +(I-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                    rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(255,0,0,255));

                    BufferChoice = I;
                }

                rectfill (BufferCard,15,5+ I*67 +(I-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 10 + 67,makeacol(130,255,255,255));

                std::ostringstream oss;

                oss << "Piste " << I+1 << " :";

                textprintf_centre_ex(BufferCard,font,(BufferCard->w )/4,(67)/2 + I*67 +(I-1)*8 + 15,makecol(0,0,0),-1,oss.str().c_str());

                textprintf_centre_ex(BufferCard,font,((BufferCard->w )/4)*3 - 30,(67)/2 + I*67 +(I-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());



            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


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
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {
                m_tabTrajets[BufferChoice]->afficherInfo(Ima2,Samp4,Music,Ima2.BuffpageAvant);
            }

        }



        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);

}

// méthode pour afficher les infos d'un sommet
void Graphe::choixSommet(Images Ima2, samples  Samp4, sound * Music)  const
{
    // Variable exit condition
    int exit_condition = 0;

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(m_tabSommets.size()); I++)
    {

        VectorName.push_back(MettreMajuscule(m_tabSommets[I]->getNom()));
    }

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

    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default


    //Buffercard Dimention

    int BuffCard_W = 444;
    int BuffCard_H =  5+ 67*NombreDeNom + ( NombreDeNom-1)* 8  +10;


    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,380);
    clear_bitmap(BufWindow);



    while (exit_condition == 0)
    {
        blit(Ima2.TODO[39],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"SUR QUEL SOMMET VOULEZ-VOUS DES INFORMATIONS?");

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
                //draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(0,0,0,255));

                //Condition pour cliquer sur l'option qu'on veut
                if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                {
                    if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ I*67 +(I-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ I*67 +(I-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                    rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(255,0,0,255));

                    BufferChoice = I;
                }

                rectfill (BufferCard,15,5+ I*67 +(I-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 10 + 67,makeacol(255,255,255,255));

                std::ostringstream oss;

                oss << "Sommet " << I+1 << " :";

                textprintf_centre_ex(BufferCard,font,(BufferCard->w )/4,(67)/2 + I*67 +(I-1)*8 + 15,makecol(0,0,0),-1,oss.str().c_str());

                textprintf_centre_ex(BufferCard,font,((BufferCard->w )/4)*3 - 30,(67)/2 + I*67 +(I-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());



            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


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
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {
                m_tabSommets[BufferChoice]->afficherInfo(Ima2,Samp4,Music,Ima2.BuffpageAvant);
            }

        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);
}


void Graphe::etudeFlotMax(Images Ima2, samples  Samp4, sound * Music)
{
    int Exit_condition = 0;
    int numSource = 10000;
    int numPuit = 0;

    bool ExitResponse = false;

    std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > > memoryTotal;

    bool Decision = false;

    Decision = choixDeuxSommet(numSource,numPuit,Ima2,Samp4,Music,false);

    if(Decision == false)
    {
        //On remet tout les flots a "0" de base pour un flot nul
        for (const auto& elem : m_tabTrajets)
        {
            elem->setFlot(0);
        }

        //Boucle de l'algorithme de Ford-Fulkerson

        while (Exit_condition == 0)
        {
            ExitResponse = parcourBFS(numSource,numPuit,memoryTotal);

            if(ExitResponse == true)
            {
                Exit_condition = 1;
            }
        }

//**************************************************************

        //Partie affichage
        afficherResultFlot(Ima2,Samp4,Music,memoryTotal,numSource,numPuit);
    }
}

//Methode de parcour BFS permettant de renvoyer les objets decouvert et leurs successeurs grace a un objet vecteur de vecteur de int
bool Graphe::parcourBFS(int NumSommetDepart, int NumSommetArrive,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >&memoryTotal)
{
    std::queue <int> FileBFS;
    std::vector <std::vector <int> > memoryBFS (m_tabSommets.size(),std::vector <int> (1,-100)); // -100 signifie non découvert ici

    int BufferNum = 0;
    int BufferFlotMinimum = 0;

    bool resultFinish = false;
    //  bool arcIndirect = false;

    std::deque <int> BufferChemin;
    std::deque <int> BufferTrajet;

    //On pousse le premié sommet dans la file
    FileBFS.push(NumSommetDepart);

    //On le marque comme decouvert
    memoryBFS[FileBFS.front()][0] = - 500; // -500 ici signifiera sommet découvert

    //std::cout << "DDD" << std::endl;

    while (FileBFS.empty() == false)
    {
        if (memoryBFS[NumSommetArrive].size() != 1)
        {
            break;
        }

        // On met les adjacences dans la file, et on garde en memoire qui est l'antécedent des nouveux sommets
        m_tabSommets[FileBFS.front()]->donnerAdjacenceBFS(FileBFS,memoryBFS);

        //On enleve le sommet devant la file, tout ces successeurs on été découvert
        FileBFS.pop();
    }

    if (memoryBFS[NumSommetArrive].size() != 1)
    {
        BufferFlotMinimum = 100000;

        BufferNum = NumSommetArrive;
        BufferChemin.push_back(BufferNum);

        do
        {
            //Pour calculer le flot minimum pour des arcs directs
            if ((m_tabTrajets [memoryBFS[BufferNum][2]]->getCapacity()) - (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot()) < BufferFlotMinimum )
            {
                BufferFlotMinimum = (m_tabTrajets [memoryBFS[BufferNum][2]]->getCapacity()) - (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot());
            }

            //Obtenr vecteur de numero des trajets utilisé (rajouter numéro arc direct)

            BufferTrajet.push_back(m_tabTrajets [memoryBFS[BufferNum][2]]->getNum());


            BufferNum = memoryBFS[BufferNum][1];

            BufferChemin.push_back(BufferNum);


        }while(BufferNum != NumSommetDepart);

        memoryTotal.push_back( std::make_pair(std::make_pair(BufferFlotMinimum,BufferChemin),BufferTrajet));

        for (unsigned int I=0; I< BufferChemin.size() -1; I++)
        {

            m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->setFlot(m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->getFlot() + BufferFlotMinimum);
        }
    }
    else
    {
        resultFinish = true;
    }
    return resultFinish;
}

void Graphe::bufferParcour(Images Ima2, samples  Samp4, sound * Music,bool UnOuDeux)
{
    if(UnOuDeux == false)
    {
        Graphe GraphoBuffer ("StationSki.txt",true);

        GraphoBuffer.FlotMaxGrapheEcart(Ima2,Samp4,Music);
    }
    else
    {
        Graphe GraphoBuffer ("StationSki.txt",false);

        GraphoBuffer.appliquerPreference();

        // GraphoBuffer.choixTrajet(Ima2,Samp4,Music);

        GraphoBuffer.dijkstraTemps(Ima2,Samp4,Music,true);

    }

}

// méthode pour récupérer les préférences
void Graphe::appliquerPreference()
{

    std::ifstream ifs{"PreferenceUser.txt"};

    int TPH_preference = 0;
    int TC_preference = 0;
    int TSD_preference = 0;
    int TS_preference = 0;
    int TK_preference = 0;
    int BUS_preference = 0;

    int V_preference = 0;
    int B_preference = 0;
    int R_preference = 0;
    int N_preference = 0;
    int KL_preference = 0;
    int SURF_preference = 0;

    int ApplicationDecision = 0;

    std::queue <int> deletionMemory;

    if (ifs)
    {
        ifs >> TPH_preference; // Pour TPH
        ifs >> TC_preference ; // Pour TC
        ifs >> TSD_preference ; // Pour TSD
        ifs >> TS_preference ; // Pour TS
        ifs >> TK_preference ; // Pour TK
        ifs >> BUS_preference ; // Pour BUS
        ifs >> V_preference ; // Pour V
        ifs >> B_preference ; // Pour B
        ifs >> R_preference ; // Pour R
        ifs >> N_preference ; // Pour N
        ifs >> KL_preference ; // Pour KL
        ifs >> SURF_preference ; // Pour SURF

        ifs.close();
    }
    else
    {
        std::cout << "Probleme ouverture fichier de donnee de preference" << std::endl;
    }

    for (int I=0; I < int (m_tabTrajets.size()); I++)
    {

        ApplicationDecision = 0;

        if ("V" == m_tabTrajets[I]->getType())
        {
            if (V_preference == 0)
            {
                ApplicationDecision = 1;
            }

        }
        else
        {
            if ("B" == m_tabTrajets[I]->getType())
            {
                if (B_preference == 0)
                {
                    ApplicationDecision = 1;
                }
            }
            else
            {
                if ("R" == m_tabTrajets[I]->getType())
                {
                    if (R_preference == 0)
                    {
                        ApplicationDecision = 1;
                    }
                }
                else
                {
                    if ("N" == m_tabTrajets[I]->getType())
                    {
                        if (N_preference == 0)
                        {
                            ApplicationDecision = 1;
                        }
                    }
                    else
                    {
                        if ("KL" == m_tabTrajets[I]->getType())
                        {
                            if (KL_preference == 0)
                            {
                                ApplicationDecision = 1;
                            }
                        }
                        else
                        {
                            if ("SURF" == m_tabTrajets[I]->getType())
                            {
                                if (SURF_preference == 0)
                                {
                                    ApplicationDecision = 1;
                                }
                            }
                            else
                            {
                                if ("TPH" == m_tabTrajets[I]->getType())
                                {
                                    if (TPH_preference == 0)
                                    {
                                        ApplicationDecision = 1;
                                    }
                                }
                                else
                                {
                                    if ("TC" == m_tabTrajets[I]->getType())
                                    {
                                        if (TC_preference == 0)
                                        {
                                            ApplicationDecision = 1;
                                        }
                                    }
                                    else
                                    {
                                        if ("TSD" == m_tabTrajets[I]->getType())
                                        {
                                            if (TSD_preference == 0)
                                            {
                                                ApplicationDecision = 1;
                                            }
                                        }
                                        else
                                        {
                                            if ("TS" == m_tabTrajets[I]->getType())
                                            {
                                                if (TS_preference == 0)
                                                {
                                                    ApplicationDecision = 1;
                                                }
                                            }
                                            else
                                            {
                                                if ("TK" == m_tabTrajets[I]->getType())
                                                {
                                                    if (TK_preference == 0)
                                                    {
                                                        ApplicationDecision = 1;
                                                    }
                                                }
                                                else
                                                {
                                                    if ("BUS" == m_tabTrajets[I]->getType())
                                                    {
                                                        if (BUS_preference == 0)
                                                        {
                                                            ApplicationDecision = 1;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        //On delete tout les trajets interdit par les preferences de l'utilisateur
        if (ApplicationDecision == 1)
        {
            //On supprime le trajet de la liste d'adjacence de ces sommets à ces extrémité
            m_tabTrajets[I]->getExtremites().first->deleteTrajet(m_tabTrajets[I]->getNum());
            m_tabTrajets[I]->getExtremites().second->deleteTrajet(m_tabTrajets[I]->getNum());

            delete m_tabTrajets[I];
            m_tabTrajets[I] = NULL;

            // m_tabTrajets.erase(m_tabTrajets.begin() + elem->getNum());
        }
    }

    //On efface les cases des trajets mis à NULL et on recommence la boucle pour tout bien effacer
    for (int I=0; I< int (m_tabTrajets.size()); I++)
    {
        if (m_tabTrajets[I] == NULL)
        {
            m_tabTrajets.erase(m_tabTrajets.begin() + I);

            I=0;
        }
    }

    //On remet tout les numero
    for (int I=0; I< int(m_tabTrajets.size()); I++)
    {
        m_tabTrajets[I]->setNum(I);
    }
}

void Graphe::FlotMaxGrapheEcart(Images Ima2, samples  Samp4, sound * Music)
{
    int Exit_condition = 0;
    int numSource = 100000;
    int numPuit = 0;

    bool ExitResponse = false;

    std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > > memoryTotal;

    bool Decision = false;

    Decision = choixDeuxSommet(numSource,numPuit,Ima2,Samp4,Music,false);

    if (Decision == false)
    {


        //On remet tout les flots a "0" de base pour un flot nul
        for (const auto& elem : m_tabTrajets)
        {
            elem->setFlot(0);
        }

//***********************************************************************
        //On peut rajouter un flot realisable pour tester l'algorithme pour les arcs indirects

//***********************************************************************

//Boucle de l'algorithme de Ford-Fulkerson
        while (Exit_condition == 0)
        {
            ExitResponse = parcourBFSGrapheEcart(numSource,numPuit,memoryTotal);

            if(ExitResponse == true)
            {
                Exit_condition = 1;
            }
        }
        afficherResultFlot(Ima2,Samp4,Music,memoryTotal,numSource,numPuit);
    }
}


void Graphe::afficherResultFlot(Images Ima2, samples  Samp4, sound * Music,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > > memoryTotal, int numSource, int numPuit)
{
    // Variable exit condition
    int exit_condition = 0;

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

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(memoryTotal.size()); I++)
    {
        std::ostringstream oss;

        oss << "CHEMIN " << I+1 << " : " << " FLOT MINIMAL DE " << memoryTotal[I].first.first;

        VectorName.push_back(oss.str().c_str());
    }

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

    system("CLS");

    //Buffercard Dimention
    int NombreDeChemin = VectorName.size();

    int BuffCard_W = 444;
    int BuffCard_H =  5+ 67*NombreDeChemin + ( NombreDeChemin-1)* 8  +10;


    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default

    int SommePourFlotTotal = 0;

    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,402 - 90);
    clear_bitmap(BufWindow);


    //On fait la somme des flots des arcs entrant du sommet d'arriver pour avoir le flot total (permet de prendre
    // en compte les eventuels flot realisable deja présent avant le lancement de l'algoritme de Ford-Fulkerson
    for (int I=0; I<int(m_tabSommets[numPuit]->getTrajets().size()); I++)
    {

        if (m_tabSommets[numPuit]->getTrajets()[I]->getExtremites().second->getNum() == numPuit)
        {
            SommePourFlotTotal = SommePourFlotTotal + m_tabSommets[numPuit]->getTrajets()[I]->getFlot();
        }
    }

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"FLOT TOTALE : %d skieurs/heure",SommePourFlotTotal);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 80,makecol(255,255,255),-1,"ENTRE %s ET %s",m_tabSommets[numSource]->getNom().c_str(),m_tabSommets[numPuit]->getNom().c_str());

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
            for (int I=0; I< NombreDeChemin; I++)
            {
                //draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(0,0,0,255));

                //Condition pour cliquer sur l'option qu'on veut
                if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                {
                    if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ I*67 +(I-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ I*67 +(I-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                    rectfill (BufferCard,10,5+ I*67 +(I-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 15 + 67,makeacol(255,0,0,255));

                    BufferChoice = I;
                }

                rectfill (BufferCard,15,5+ I*67 +(I-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ I*67 +(I-1)*8 + 10 + 67,makeacol(255,255,255,255));


                textprintf_centre_ex(BufferCard,font,((BufferCard->w )/2),(67)/2 + I*67 +(I-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());

            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


        if (VectorName.size()>4)
        {
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

        }


        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {


                //On remet tout les flots a "0" de base pour un flot nul
                for (const auto& elem : m_tabTrajets)
                {
                    elem->setFlot(0);
                }

                //On rajoute les flots des chemin précedant notre chemin si il y en a
                for (int J=0; J< BufferChoice; J++)
                {
                    afficherResultChemin(Ima2,Samp4,Music,memoryTotal,J,false);
                }

                //Affichage du chemin avec ces flots
                afficherResultChemin(Ima2,Samp4,Music,memoryTotal,BufferChoice,true);
            }

        }


        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);




    std::cout << std::endl <<"Le flot totale trouver entre le sommet " << m_tabSommets[numSource]->getNom() << " vers le sommet " << m_tabSommets[numPuit]->getNom() << " est de : " <<  SommePourFlotTotal << std::endl << std::endl << std::endl;

    for (int  I=0; I< int(memoryTotal.size()); I++)
    {
        std::cout <<"Chemin " << I+1 << " : La valeur de flot minimum est : " <<  memoryTotal[I].first.first << " , le chemin trouver est : "  << std::endl << std::endl;

        for (int J= int (memoryTotal[I].second.size() -1); J >= 0; J--)
        {

            //On redonne le flot du chemin additionner au flot minimum trouver pour ce chemin pour voir l'evolution des flots par chemin
            m_tabTrajets[memoryTotal[I].second[J]]->setFlot(m_tabTrajets[memoryTotal[I].second[J]]->getFlot() + memoryTotal[I].first.first);


            //Affichage premier sommet
            std::cout << "[ " << m_tabSommets[memoryTotal[I].first.second[J+1]]->getNom() << " {" << memoryTotal[I].first.second[J+1] + 1 << "} ]" ;

            //Affichage trajet emprunter entre les deux sommets
            std::cout << "-- "<< m_tabTrajets[memoryTotal[I].second[J]]->getNom()<< "<" << m_tabTrajets[memoryTotal[I].second[J]]->getFlot() <<"/" << m_tabTrajets[memoryTotal[I].second[J]]->getCapacity() << ">" <<" {" << m_tabTrajets[memoryTotal[I].second[J]]->getNum() + 1 << "} -->";

            //Affichage deuxième sommet
            std::cout << "[ " << m_tabSommets[memoryTotal[I].first.second[J]]->getNom() << " {" << memoryTotal[I].first.second[J] + 1 << "} ]  ,"  << std::endl;


        }


        std::cout << std::endl<< std::endl << std::endl;
    }

    std::cout << std::endl;

}

void Graphe::afficherResultChemin(Images Ima2, samples  Samp4, sound * Music,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >memoryTotal, int place, bool BufferToPlace)
{
    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (0);
    int posButtonExit_X = 20,posButtonExit_Y = 20;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;



    std::ostringstream oss[int(memoryTotal[place].second.size())];


    for (int J= int (memoryTotal[place].second.size() -1); J >= 0; J--)
    {

        //On redonne le flot du chemin additionner au flot minimum trouver pour ce chemin pour voir l'evolution des flots par chemin
        m_tabTrajets[memoryTotal[place].second[J]]->setFlot(m_tabTrajets[memoryTotal[place].second[J]]->getFlot() + memoryTotal[place].first.first);


        //Affichage premier sommet
        oss[J] << "[ " << m_tabSommets[memoryTotal[place].first.second[J+1]]->getNom() << " {" << memoryTotal[place].first.second[J+1] + 1 << "} ]" ;


        //Affichage trajet emprunter entre les deux sommets
        oss[J] << "-- "<< m_tabTrajets[memoryTotal[place].second[J]]->getNom()<< " |" << m_tabTrajets[memoryTotal[place].second[J]]->getType() <<"| "  << "<" << m_tabTrajets[memoryTotal[place].second[J]]->getFlot() <<"/" << m_tabTrajets[memoryTotal[place].second[J]]->getCapacity() << ">" <<" {" << m_tabTrajets[memoryTotal[place].second[J]]->getNum() + 1 << "} -->";



        //Affichage deuxième sommet
        oss[J] << "[ " << m_tabSommets[memoryTotal[place].first.second[J]]->getNom() << " {" << memoryTotal[place].first.second[J] + 1 << "} ]  ,";

    }


    if (BufferToPlace == true)
    {
        while (exit_condition == 0)
        {
            blit(Ima2.TODO[42],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 110,makecol(255,255,255),-1,"FLOT MINIMAL DU CHEMIN %d: %d skieurs/heure",place+1,memoryTotal[place].first.first);

            for (int J= int (memoryTotal[place].second.size() -1); J >= 0; J--)
            {

                textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 80 + (memoryTotal[place].second.size() -1 - J) * 25,makecol(255,255,255),-1,MettreMajuscule(oss[J].str()).c_str());

            }


            ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
            if ( ExitResponse == true )
            {
                exit_condition = 1;
            }

            blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        }

    }

}



bool Graphe::parcourBFSGrapheEcart(int NumSommetDepart, int NumSommetArrive,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >&memoryTotal)
{
    std::queue <int> FileBFS;
    std::vector <std::vector <int> > memoryBFS (m_tabSommets.size(),std::vector <int> (1,-100)); // -100 signifie non découvert ici

    int BufferNum = 0;
    int BufferFlotMinimum = 0;
    bool resultFinish = false;

    std::deque <int> BufferChemin;
    std::deque <int> BufferTrajet;

    //On pousse le premié sommet dans la file
    FileBFS.push(NumSommetDepart);

    //On le marque comme decouvert
    memoryBFS[FileBFS.front()][0] = - 500; // -500 ici signifiera sommet découvert


    while (FileBFS.empty() == false)
    {
        if (memoryBFS[NumSommetArrive].size() == 2)
        {
            break;
        }

        // On met les adjacences dans la file, et on garde en memoire qui est l'antécedent des nouveux sommets
        m_tabSommets[FileBFS.front()]->donnerAdjacenceBFSGraphEcart(FileBFS,memoryBFS);

        //On enleve le sommet devant la file, tout ces successeurs on été découvert
        FileBFS.pop();

    }


    if (memoryBFS[NumSommetArrive].size() != 1)
    {
        BufferFlotMinimum = 100000;

        BufferNum = NumSommetArrive;
        BufferChemin.push_back(BufferNum);

        do
        {
            //Obtenir le flot minimum

            if (memoryBFS[BufferNum][2] >= 0)
            {
                memoryBFS[BufferNum][2] = memoryBFS[BufferNum][2] + memoryBFS[BufferNum][2];

                if ((m_tabTrajets [memoryBFS[BufferNum][2]]->getCapacity()) - (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot()) < BufferFlotMinimum )
                {
                    BufferFlotMinimum = (m_tabTrajets [memoryBFS[BufferNum][2]]->getCapacity()) - (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot());
                }

            }
            else
            {
                memoryBFS[BufferNum][2] = (memoryBFS[BufferNum][2] +1) *(-1);

                memoryBFS[BufferNum][2] = memoryBFS[BufferNum][2] + memoryBFS[BufferNum][2] +1;

                if (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot() < BufferFlotMinimum )
                {
                    BufferFlotMinimum = (m_tabTrajets [memoryBFS[BufferNum][2]]->getFlot());
                }
            }


            //Obtenr vecteur de numero des trajets utilisé
            BufferTrajet.push_back(memoryBFS[BufferNum][2]);

            BufferNum = memoryBFS[BufferNum][1];

            BufferChemin.push_back(BufferNum);


        }
        while(BufferNum != NumSommetDepart);


        memoryTotal.push_back( std::make_pair(std::make_pair(BufferFlotMinimum,BufferChemin),BufferTrajet));


        for (unsigned int I=0; I< BufferChemin.size() -1; I++)
        {
            if (m_tabTrajets[memoryBFS[BufferChemin[I]][2]]->getCapacity() != 1000000)
            {
                //On augmente le flot du chemin direct
                m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->setFlot(m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->getFlot() + BufferFlotMinimum);

                //On diminue le flot du chemin indirect parallele au chemin direct, present la case d'apres
                m_tabTrajets [memoryBFS[BufferChemin[I]][2] + 1]->setFlot(m_tabTrajets [memoryBFS[BufferChemin[I]][2] + 1]->getFlot() - BufferFlotMinimum);
            }
            else
            {
                //On diminue le flot du chemin indirect
                m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->setFlot(m_tabTrajets [memoryBFS[BufferChemin[I]][2]]->getFlot() - BufferFlotMinimum);

                //On augmente le flot du chemin direct parallele au chemin indirect, present a la case d'avant
                m_tabTrajets [memoryBFS[BufferChemin[I]][2]-1]->setFlot(m_tabTrajets [memoryBFS[BufferChemin[I]][2]-1]->getFlot() + BufferFlotMinimum);


            }


        }


    }
    else
    {
        resultFinish = true;
    }

    return resultFinish;

}

bool Graphe::choixUnSommet(int& sommet1,Images Ima2, samples  Samp4, sound * Music)
{
    // Variable exit condition
    int exit_condition = 0;


    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(m_tabSommets.size()); I++)
    {
        VectorName.push_back(MettreMajuscule(m_tabSommets[I]->getNom()));
    }

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

    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default

    int BufferShowSommet = 0;

    //Buffercard Dimention

    int BuffCard_W = 444;

    int BuffCard_H =  5+ 67*NombreDeNom + ( NombreDeNom-1)* 8  +10;


    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,380);
    clear_bitmap(BufWindow);


    bool decision = false;
    // bool bufferDecision = false;

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);


        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"QUEL SOMMET VOULEZ-VOUS POUR LE SOMMET DE DEPART?");


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;

            sommet1 = 1000000;
            decision = true;
        }

        //Afficher les noms des fonctionnalité possible
        clear_bitmap(BufWindow);
        rectfill (BufWindow,0,0,BufWindow->w,BufWindow->h,makeacol(255,0,255,255));
        clear_bitmap(BufferCard);
        rectfill (BufferCard,0,0,BufferCard->w,BufferCard->h,makeacol(255,0,255,255));


        if (VectorName.size() != 0)
        {
            BufferShowSommet = 0;

            // BuffAffiche = 0;
            for (int I=0; I< int(VectorName.size()); I++)
            {
                //draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                if (I != sommet1)
                {
                    rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(0,0,0,255));

                    //Condition pour cliquer sur l'option qu'on veut
                    if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                    {
                        if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                        rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(255,0,0,255));

                        BufferChoice = I;
                    }

                    rectfill (BufferCard,15,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 10 + 67,makeacol(255,255,255,255));

                    std::ostringstream oss;

                    oss << "Sommet " << I+1 << " :";

                    textprintf_centre_ex(BufferCard,font,(BufferCard->w )/4,(67)/2 + BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,makecol(0,0,0),-1,oss.str().c_str());

                    textprintf_centre_ex(BufferCard,font,((BufferCard->w )/4)*3 - 30,(67)/2 + BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());

                    BufferShowSommet++;
                }

            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


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
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {

                sommet1 = BufferChoice;


                exit_condition = 1;

            }

        }


        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);


    return decision;

}

bool Graphe::choixDeuxSommet(int& sommet1,int& sommet2,Images Ima2, samples  Samp4, sound * Music, bool Sommet2True)
{
    // Variable exit condition
    int exit_condition = 0;


    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(m_tabSommets.size()); I++)
    {
        VectorName.push_back(MettreMajuscule(m_tabSommets[I]->getNom()));
    }

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

    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default

    int BufferShowSommet = 0;

    //Buffercard Dimention

    int BuffCard_W = 444;

    if (Sommet2True == true)
    {
        NombreDeNom = NombreDeNom -1;
    }

    int BuffCard_H =  5+ 67*NombreDeNom + ( NombreDeNom-1)* 8  +10;


    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,380);
    clear_bitmap(BufWindow);


    bool decision = false;
    bool bufferDecision = false;

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);

        if (Sommet2True == false)
        {
            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"QUEL SOMMET VOULEZ-VOUS POUR LE SOMMET DE DEPART?");
        }
        else
        {
            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"QUEL SOMMET VOULEZ-VOUS POUR LE SOMMET D ARRIVEE?");
        }


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;

            sommet1 = 1000000;
            decision = true;
        }

        //Afficher les noms des fonctionnalité possible
        clear_bitmap(BufWindow);
        rectfill (BufWindow,0,0,BufWindow->w,BufWindow->h,makeacol(255,0,255,255));
        clear_bitmap(BufferCard);
        rectfill (BufferCard,0,0,BufferCard->w,BufferCard->h,makeacol(255,0,255,255));


        if (VectorName.size() != 0)
        {
            BufferShowSommet = 0;

            // BuffAffiche = 0;
            for (int I=0; I< int(VectorName.size()); I++)
            {
                //draw_sprite (BufferCard,Ima2.TODO[10],10,5+ I*67 +(I-1)*8 + 15); //67 de base la taille

                if (I != sommet1)
                {
                    rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(0,0,0,255));

                    //Condition pour cliquer sur l'option qu'on veut
                    if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                    {
                        if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                        rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(255,0,0,255));

                        BufferChoice = I;
                    }

                    rectfill (BufferCard,15,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 10 + 67,makeacol(255,255,255,255));

                    std::ostringstream oss;

                    oss << "Sommet " << I+1 << " :";

                    textprintf_centre_ex(BufferCard,font,(BufferCard->w )/4,(67)/2 + BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,makecol(0,0,0),-1,oss.str().c_str());

                    textprintf_centre_ex(BufferCard,font,((BufferCard->w )/4)*3 - 30,(67)/2 + BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());

                    BufferShowSommet++;
                }

            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


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
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {
                if (Sommet2True == false)
                {
                    sommet1 = BufferChoice;

                    bufferDecision = choixDeuxSommet(sommet1,sommet2,Ima2,Samp4,Music,true);

                    if (bufferDecision == false)
                    {
                        exit_condition = 1;
                    }

                }
                else
                {
                    sommet2 = BufferChoice;

                    exit_condition = 1;
                }
            }

        }


        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);


    return decision;

}

void Graphe::modifValPreference(Images Ima2, samples  Samp4, sound * Music)
{
    // Variable exit condition
    int exit_condition = 0;

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


    std::ifstream ifs{"PreferenceUser.txt"};

    int TabVal[12];

    if (ifs)
    {
        ifs >> TabVal[0] ; // Pour TPH
        ifs >> TabVal[1] ; // Pour TC
        ifs >> TabVal[2] ; // Pour TSD
        ifs >> TabVal[3] ; // Pour TS
        ifs >> TabVal[4] ; // Pour TK
        ifs >> TabVal[5] ; // Pour BUS
        ifs >> TabVal[6] ; // Pour V
        ifs >> TabVal[7] ; // Pour B
        ifs >> TabVal[8] ; // Pour R
        ifs >> TabVal[9] ; // Pour N
        ifs >> TabVal[10] ; // Pour KL
        ifs >> TabVal[11] ; // Pour SURF

        ifs.close();
    }
    else
    {
        std::cout << "Probleme ouverture fichier de donnee de preference" << std::endl;
    }


    std::vector <std::string> TabName;

    TabName.push_back("TELEPHERIQUE :");
    TabName.push_back("TELECABINE :");
    TabName.push_back("TELESIEGE DEBRAYABLE :");
    TabName.push_back("TELESIEGE:");
    TabName.push_back("TELESKI :");
    TabName.push_back("NAVETTES :");

    TabName.push_back("PISTE VERT :");
    TabName.push_back("PISTE BLEU :");
    TabName.push_back("PISTE ROUGE :");
    TabName.push_back("PISTE NOIR :");
    TabName.push_back("PISTE KILOMETRE LANCE :");
    TabName.push_back("SNOWPARK :");


    //Partie pour les boutons pour changer les valeurs contenu dans les peties fenetre
    int RadiusSquare = 0;

    int buttonPlus_X = 0;
    int buttonPlus_Y = 0;
    int buttonMoins_X = 0;
    int buttonMoins_Y = 0;

    int RayonPlusMoins = 13;

    int NumberOfOption = 12;
    int buttonMoins_condition [NumberOfOption];

    for (int I=0; I<NumberOfOption ; I++)
    {
        buttonMoins_condition[I] = 0;
    }

    int buttonPlus_condition [NumberOfOption];

    for (int I=0; I<NumberOfOption ; I++)
    {
        buttonPlus_condition[I] = 0;
    }

    int SoundCondition_Moins [NumberOfOption];
    for (int I=0; I<NumberOfOption; I++)
    {
        SoundCondition_Moins[I] = 1;
    }

    int SoundCondition_Plus [NumberOfOption];
    for (int I=0; I<NumberOfOption; I++)
    {
        SoundCondition_Plus[I] = 1;
    }



    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"PARAMETRAGE PREFERENCE UTILISATEUR:");


        for (int I=0; I< 12; I++)
        {

            textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 165,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 50 + I*30,makecol(255,255,255),-1,TabName[I].c_str());

            //Partie bouton moins
            buttonMoins_X = (SCREEN_W )/2 + 110 - 26  - 20;
            buttonMoins_Y = (SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 45 + I*30;


            RadiusSquare = ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ ( buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) * ( buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {

                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X,buttonMoins_Y );
                buttonMoins_condition [I]= 1;


                if((SoundCondition_Moins[I] == 1) && (Music->music_on == true))
                {

                    play_sample(Samp4.press_button_1,Music->volume,128,1000,0);


                    SoundCondition_Moins[I] = 0;
                }
            }

            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonMoins_condition [I] == 1)
                {
                    if(Music->music_on == true)
                    {

                        play_sample(Samp4.press_button_2,Music->volume,128,1000,0);


                        SoundCondition_Moins[I] = 1;

                    }

                    TabVal [I]--;

                    buttonMoins_condition [I] = 0;
                }


                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);

            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonMoins_condition [I] = 0;
                SoundCondition_Moins[I] = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);
            }



            //Partie bouton Plus
            buttonPlus_X = (SCREEN_W )/2 + 110 + 33 + 20;
            buttonPlus_Y = (SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 45 + I*30;


            RadiusSquare = ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) * (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {

                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X,buttonPlus_Y );
                buttonPlus_condition [I]= 1;


                if((SoundCondition_Plus[I] == 1) && (Music->music_on == true))
                {

                    play_sample(Samp4.press_button_1,Music->volume,128,1000,0);

                    SoundCondition_Plus[I] = 0;
                }
            }
            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonPlus_condition [I] == 1)
                {
                    if(Music->music_on == true)
                    {

                        play_sample(Samp4.press_button_2,Music->volume,128,1000,0);

                        SoundCondition_Plus[I] = 1;

                    }

                    TabVal [I]++;

                    buttonPlus_condition [I] = 0;
                }

                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);

            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonPlus_condition [I] = 0;
                SoundCondition_Plus[I] = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);
            }

            if (TabVal[I] >= 1)
            {
                TabVal[I] = 1;
            }

            if (TabVal[I] <= 0)
            {
                TabVal[I] = 0;
            }

            if (TabVal[I] == 1)
            {
                textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2 + 115 + (Ima2.TODO[5]->w/2),(SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 40 + I*30 + (Ima2.TODO[5]->h/2),makecol(255,255,255),-1,"OUI");

            }
            else
            {
                textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2 + 115 + (Ima2.TODO[5]->w/2),(SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 40 + I*30 + (Ima2.TODO[5]->h/2),makecol(255,0,0),-1,"NON");

            }


        }


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {


            std::ofstream FicData("PreferenceUser.txt", std::ios::out);
            if (FicData)
            {
                for (int I =0; I< 12; I++)
                {
                    FicData << TabVal[I] << std::endl;
                }


                FicData.close();
            }
            else
            {
                std::cout << "ERREUR : probleme lors de la réecriture des donnee dans preferenceUser" << std::endl;
            }

            exit_condition = 1;

        }


        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}

void Graphe::modifValFlot(Images Ima2, samples  Samp4, sound * Music)
{
    // Variable exit condition
    int exit_condition = 0;

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


    int TabVal[12];

    TabVal[0] = m_data.TPH_info[0];
    TabVal[1] = m_data.TC_info[0];
    TabVal[2] = m_data.TSD_info[0];
    TabVal[3] = m_data.TS_info[0];
    TabVal[4] = m_data.TK_info[0];
    TabVal[5] = m_data.BUS_info[0];
    TabVal[6] = m_data.V_info[0];
    TabVal[7] = m_data.B_info[0];
    TabVal[8] = m_data.R_info[0];
    TabVal[9] = m_data.N_info[0];
    TabVal[10] = m_data.KL_info[0];
    TabVal[11] = m_data.SURF_info[0];


    std::vector <std::string> TabName;

    TabName.push_back("TELEPHERIQUE :");
    TabName.push_back("TELECABINE :");
    TabName.push_back("TELESIEGE DEBRAYABLE :");
    TabName.push_back("TELESIEGE:");
    TabName.push_back("TELESKI :");
    TabName.push_back("NAVETTES :");

    TabName.push_back("PISTE VERT :");
    TabName.push_back("PISTE BLEU :");
    TabName.push_back("PISTE ROUGE :");
    TabName.push_back("PISTE NOIR :");
    TabName.push_back("PISTE KILOMETRE LANCE :");
    TabName.push_back("SNOWPARK :");


    //Partie pour les boutons pour changer les valeurs contenu dans les peties fenetre
    int RadiusSquare = 0;

    int buttonPlus_X = 0;
    int buttonPlus_Y = 0;
    int buttonMoins_X = 0;
    int buttonMoins_Y = 0;

    int RayonPlusMoins = 13;

    int NumberOfOption = 12;
    int buttonMoins_condition [NumberOfOption];

    for (int I=0; I<NumberOfOption ; I++)
    {
        buttonMoins_condition[I] = 0;
    }

    int buttonPlus_condition [NumberOfOption];

    for (int I=0; I<NumberOfOption ; I++)
    {
        buttonPlus_condition[I] = 0;
    }

    int SoundCondition_Moins [NumberOfOption];
    for (int I=0; I<NumberOfOption; I++)
    {
        SoundCondition_Moins[I] = 1;
    }

    int SoundCondition_Plus [NumberOfOption];
    for (int I=0; I<NumberOfOption; I++)
    {
        SoundCondition_Plus[I] = 1;
    }

    int Buffer = 0;

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"PARAMETRAGE FLOT (en skieurs/heure):");


        for (int I=0; I< 12; I++)
        {

            textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 165,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 50 + I*30,makecol(255,255,255),-1,TabName[I].c_str());

            //Partie bouton moins
            buttonMoins_X = (SCREEN_W )/2 + 110 - 26  - 20;
            buttonMoins_Y = (SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 45 + I*30;


            RadiusSquare = ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonMoins_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ ( buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) * ( buttonMoins_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {

                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X,buttonMoins_Y );
                buttonMoins_condition [I]= 1;

                TabVal [I]--;

                if((SoundCondition_Moins[I] == 1) && (Music->music_on == true))
                {

                    play_sample(Samp4.press_button_1,Music->volume,128,1000,0);


                    SoundCondition_Moins[I] = 0;
                }
            }

            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonMoins_condition [I] == 1)
                {
                    if(Music->music_on == true)
                    {

                        play_sample(Samp4.press_button_2,Music->volume,128,1000,0);


                        SoundCondition_Moins[I] = 1;

                    }

                    buttonMoins_condition [I] = 0;
                }

                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);

            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonMoins_condition [I] = 0;
                SoundCondition_Moins[I] = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonMoins_X + (Ima2.TODO[6]->w)/2, buttonMoins_Y + (Ima2.TODO[6]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[6],buttonMoins_X - 3,buttonMoins_Y - 3);
            }



            //Partie bouton Plus
            buttonPlus_X = (SCREEN_W )/2 + 110 + 33 + 20;
            buttonPlus_Y = (SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 45 + I*30;


            RadiusSquare = ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x) * ( buttonPlus_X+ Ima2.TODO[5]->w/ 2 - mouse_x)+ (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) * (buttonPlus_Y + Ima2.TODO[5]->h / 2 - mouse_y) ;

            if ((RadiusSquare < RayonPlusMoins*RayonPlusMoins) && (mouse_b&1))
            {

                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X,buttonPlus_Y );
                buttonPlus_condition [I]= 1;

                TabVal [I]++;

                if((SoundCondition_Plus[I] == 1) && (Music->music_on == true))
                {

                    play_sample(Samp4.press_button_1,Music->volume,128,1000,0);

                    SoundCondition_Plus[I] = 0;
                }
            }

            // verify if we left-click on the mouse
            else if (!mouse_b&1)
            {
                // if the mouse is on the exit button it will exit from the infinit loop
                if (  buttonPlus_condition [I] == 1)
                {
                    if(Music->music_on == true)
                    {

                        play_sample(Samp4.press_button_2,Music->volume,128,1000,0);

                        SoundCondition_Plus[I] = 1;

                    }

                    buttonPlus_condition [I] = 0;
                }

                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);

            }

            // we don't left-click and we aren't on a button
            else
            {
                // put variables as default
                buttonPlus_condition [I] = 0;
                SoundCondition_Plus[I] = 1;

                // draw the buttons on their normal position
                circlefill(Ima2.page, buttonPlus_X + (Ima2.TODO[5]->w)/2, buttonPlus_Y + (Ima2.TODO[5]->h)/2, RayonPlusMoins, makeacol(0, 0, 0, 200));
                draw_sprite (Ima2.page,Ima2.TODO[5],buttonPlus_X - 3,buttonPlus_Y - 3);
            }

            if (TabVal[I] >= 20000)
            {
                TabVal[I] = 20000;
            }

            if (TabVal[I] <= 0)
            {
                TabVal[I] = 0;
            }

            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2 + 115 + (Ima2.TODO[5]->w/2),(SCREEN_H - Ima2.TODO[9]->h)/2 + 60 + 40 + I*30 + (Ima2.TODO[5]->h/2),makecol(255,255,255),-1,"%d",TabVal[I]);

        }


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {
            m_data.TPH_info[0] = TabVal[0];
            m_data.TC_info[0] = TabVal[1];
            m_data.TSD_info[0] = TabVal[2];
            m_data.TS_info[0] = TabVal[3];
            m_data.TK_info[0] = TabVal[4];
            m_data.BUS_info[0] = TabVal[5];
            m_data.V_info[0] = TabVal[6];
            m_data.B_info[0] = TabVal[7];
            m_data.R_info[0] = TabVal[8];
            m_data.N_info[0] = TabVal[9];
            m_data.KL_info[0] = TabVal[10];
            m_data.SURF_info[0] = TabVal[11];


            std::ofstream FicData("dataUser.txt", std::ios::out);
            if (FicData)
            {
                for (int I=0; I< 12 ; I++)
                {
                    if ((I>=0)&&(I<=4))
                    {
                        Buffer = nbInfo+1;
                    }
                    else
                    {
                        Buffer = nbInfo;
                    }

                    for (int J=0; J< Buffer ; J++)
                    {
                        switch (I)
                        {

                        case 0 :
                            FicData << m_data.TPH_info[J] << " ";
                            break;

                        case 1 :
                            FicData << m_data.TC_info[J]<< " ";
                            break;

                        case 2 :
                            FicData <<  m_data.TSD_info[J]<< " ";
                            break;

                        case 3 :
                            FicData <<  m_data.TS_info[J]<< " ";
                            break;

                        case 4 :
                            FicData <<  m_data.TK_info[J]<< " ";
                            break;

                        case 5 :
                            FicData <<  m_data.BUS_info[J]<< " ";
                            break;

                        case 6 :
                            FicData <<  m_data.V_info[J]<< " ";
                            break;

                        case 7 :
                            FicData <<  m_data.B_info[J]<< " ";
                            break;

                        case 8 :
                            FicData <<  m_data.R_info[J]<< " ";
                            break;

                        case 9 :
                            FicData <<  m_data.N_info[J]<< " ";
                            break;

                        case 10 :
                            FicData <<  m_data.KL_info[J]<< " ";
                            break;

                        case 11 :
                            FicData <<  m_data.SURF_info[J]<< " ";
                            break;
                        }
                    }

                    FicData << std::endl;

                }


                FicData.close();
            }
            else
            {
                std::cout << "ERREUR : probleme lors de la réecriture des donnee dans dataUser" << std::endl;
            }

            //On change les capacité en accord avec les modifications

            for (int I =0; I< int(m_tabTrajets.size()); I++)
            {
                if ("V" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.V_info[0]);
                }

                if ("B" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.B_info[0]);
                }

                if ("R" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.R_info[0]);
                }

                if ("N" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.N_info[0]);
                }


                if ("KL" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.KL_info[0]);
                }


                if ("SURF" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.SURF_info[0]);
                }


                if ("TPH" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.TPH_info[0]);
                }


                if ("TC" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.TC_info[0]);
                }


                if ("TSD" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.TSD_info[0]);
                }


                if ("TS" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.TS_info[0]);
                }

                if ("TK" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity( m_data.TK_info[0]);
                }

                if ("BUS" == m_tabTrajets[I]->getType())
                {
                    m_tabTrajets[I]->setCapacity(m_data.BUS_info[0]);
                }


            }

            exit_condition = 1;

        }


        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }


}


const std::vector<Trajet *> &Graphe::getTabTrajets() const
{
    return m_tabTrajets;
}

void Graphe::setTabTrajets(Trajet* nouveauTrajet)
{
    m_tabTrajets.push_back(nouveauTrajet);
}

const std::vector<Sommet*> &Graphe::getTabSommets() const
{
    return m_tabSommets;
}

void Graphe::setTabSommets(Sommet* nouveauSommet)
{
    m_tabSommets.push_back(nouveauSommet);
}

void Graphe::BFS2(Images Ima2, samples  Samp4, sound * Music)
{

    int sommet1 = 10000;
    int sommet2 = 0;
    bool decision = false;

    std::queue <int> FileBFS;
    std::vector <std::vector <int> > memoryBFS (m_tabSommets.size(),std::vector <int> (1,-100)); // -100 signifie non découvert ici

    int BufferNum = 0;


    std::deque <int> BufferChemin;
    std::deque <int> BufferTrajet;

    //Programme pour choisir le sommet de depart du BFS
    decision = choixDeuxSommet(sommet1,sommet2,Ima2,Samp4,Music,false);

    // std::cout << sommet1 << std::endl;

    if (decision == false)
    {
        //On pousse le premié sommet dans la file
        FileBFS.push(sommet1);

        //On le marque comme decouvert
        memoryBFS[FileBFS.front()][0] = - 500; // -500 ici signifiera sommet découvert

        //On remet tout les flots a "0" de base pour un flot nul pour reutiliser le BFS des flots
        for (const auto& elem : m_tabTrajets)
        {
            elem->setFlot(0);
        }

        while (FileBFS.empty() == false)
        {

            //std::cout << "AAA ";

            // On met les adjacences dans la file, et on garde en memoire qui est l'antécedent des nouveux sommets
            m_tabSommets[FileBFS.front()]->donnerAdjacenceBFS(FileBFS,memoryBFS);

            //std::cout << "BBB" << std::endl;

            //On enleve le sommet devant la file, tout ces successeurs on été découvert
            FileBFS.pop();

        }

        system("CLS");



        if (memoryBFS[sommet2] [0] == 500) // Le sommet choisi au debut est forcément pas pris en compte, vue qu'il n'a pas de sommet
        {
            // qui la decouvert
            std::cout << sommet2;

            BufferNum = sommet2;
            do
            {
                BufferNum = memoryBFS[BufferNum][1];

                std::cout << " <-- ";

                std::cout << BufferNum;

            }
            while(BufferNum != sommet1);

            std::cout << std::endl;
        }


        //Affichage des resultats en mode graphique
        affichResultatBFS(Ima2,Samp4,Music,memoryBFS,sommet2-1,sommet2+1,sommet1,true,sommet2,false);

    }

}


void Graphe::dijkstraTemps(Images Ima2, samples  Samp4, sound * Music,bool UnDeux)
{

    int sommet1 = 10000;
    int sommet2 = 0;
    bool decision = false;

    // File de priorité pour acceder facilement au sommet ayant la plus petite distance
    // Utilise une fonction de comparaison personnalisé développer dans le header
    std::priority_queue <std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int> >,comparaison> filePriority;

    // Vecteur de vecteur de la taille du nombre de sommet
    //La première case du second vecteur definit si sommet decouvert ou pas
    //La deuxième case du second vecteur definit la distance par rapport au sommet initial
    //La troisième case du second vecteur donne le prédecesseur du sommet
    std::vector <std::vector<int>> MemorySommet (m_tabSommets.size(),std::vector <int> (1,-100)); // "-100" signifie sommet non découvert ici

    //Variable d'affichage des résultats
    int BufferAffichage = 0;
    std::stack <int> PileAffichage;
    int SommeTotalDistance = 0;

    if(UnDeux == false)
    {
        //Programme pour choisir le sommet de depart de djikstra
        decision = choixUnSommet(sommet1,Ima2,Samp4,Music);
    }
    else
    {
        //Programme pour choisir le sommet de depart  et d'arrivé de djikstra
        decision = choixDeuxSommet(sommet1,sommet2,Ima2,Samp4,Music,false);
    }



    if (decision == false)
    {
        for (int I =0; I< int(m_tabSommets.size()); I++)
        {
            //On met tout les sommets à zero de distance comme du sommet de départ comme initialisation
            MemorySommet[I].push_back(0);

            //On initialise la case contenant plus tard les prédecesseurs des sommets
            MemorySommet[I].push_back(0);

            //On initialise la case contenant plus tard le numero du trajet qui la decouvert
            MemorySommet[I].push_back(0);
        }

        //On met le sommet de depart dans la file
        filePriority.push(std::make_pair(m_tabSommets[sommet1],0));

        //On remet tout les flots a "0" de base pour un flot nul pour reutiliser le BFS des flots
        for (const auto& elem : m_tabTrajets)
        {
            elem->setFlot(0);
        }


        while(filePriority.empty() != true)
        {

            // std::cout << "AAA ";
            //Methode de la classe sommet permetant de faire le traitement des adjacences du sommet facon djikstra,
            // m'étant entre autre les sommets decouvert dans la priorityQueue
            m_tabSommets[filePriority.top().first->getNum()]->AdjacenceDjikstra(filePriority, MemorySommet);

            // std::cout << "BBB" << std::endl;
        }


        system("CLS");


        for (int I=0; I< int(MemorySommet.size()); I++)
        {
            if (MemorySommet[I][0] == -500)
            {
                if (I != sommet1)
                {
                    //...sinon on affiche le chemin parcourue et leurs poids avait chaque fois
                    std::cout << I;

                    // Affichage du chemin parcourue dans un premier temps
                    BufferAffichage = I;

                    do
                    {
                        PileAffichage.push(BufferAffichage);//On garde en memoire les numeros de sommet dans une pile pour l'affichage
                        // des poids plus tard

                        BufferAffichage = MemorySommet[BufferAffichage][2]; //On remonte avec cette action la liste des successeur
                        //jusqu'au sommet de depart
                        std::cout << " <-- ";
                        std::cout << BufferAffichage;

                    }
                    while(BufferAffichage != sommet1);

                    // PileAffichage.push(sommet1);

                    // std::cout << std::endl;

                    // Affichage des poids du chemin parcourue dans un deuxième temps, en utilisant la pile creer précédement
                    std::cout << "  : longueur ";

                    SommeTotalDistance = 0;

                    while(PileAffichage.empty() != true)
                    {
                        BufferAffichage = PileAffichage.top();
                        PileAffichage.pop();

                        // if (PileAffichage.size() >= 1)
                        // {
                        //Sous programme donnant le poid d'une adjacence donné d'un sommet
                        //  std::cout <<  afficherSecondeEnTemps(m_tabSommets[BufferAffichage]->DistanceAdjacence(PileAffichage.top()));

                        //  SommeTotalDistance = SommeTotalDistance + m_tabSommets[BufferAffichage]->DistanceAdjacence(PileAffichage.top()) ;

                        std::cout <<  afficherSecondeEnTemps(transformerTempsEnSeconde(m_tabTrajets[MemorySommet[BufferAffichage][3]]->getTempsTrajet()));

                        SommeTotalDistance = SommeTotalDistance + transformerTempsEnSeconde(m_tabTrajets[MemorySommet[BufferAffichage][3]]->getTempsTrajet()) ;
                        // }


                        if (PileAffichage.size() >= 1)
                        {
                            std::cout << " + ";
                        }
                    }

                    //Affichage de la somme totale
                    std::cout << " = " << afficherSecondeEnTemps(SommeTotalDistance) << std::endl;


                }
            }

        }

        if (UnDeux == false)
        {
            //On reutilise l'affichage du résultat primère utiliser pour le BFS
            affichResultatBFS(Ima2,Samp4,Music,MemorySommet,-1,37,sommet1,false,0,true);
        }
        else
        {
            //On reutilise l'affichage du résultat primère utiliser pour le BFS
            affichResultatBFS(Ima2,Samp4,Music,MemorySommet,sommet2-1,sommet2+1,sommet1,false,sommet2,true);
        }

    }

}

void Graphe::affichDjikstraTrajet(Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector<int>> MemorySommet, int numSource, int numArivee)
{
    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (0);
    int posButtonExit_X = 20,posButtonExit_Y = 20;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;


    int BufferNum = 0;
    int NumbEtape = 0;

    int SommeTotalDistance = 0;

    if (MemorySommet[numArivee][0] == -500)
    {
        //On trouve le nombre d'etape pour passer du sommet de depart à celui d'arriver
        BufferNum = numArivee;
        do
        {
            SommeTotalDistance = SommeTotalDistance + transformerTempsEnSeconde(m_tabTrajets[MemorySommet[BufferNum][3]]->getTempsTrajet()) ;

            BufferNum = MemorySommet[BufferNum][2];

            NumbEtape++;
        }
        while(BufferNum != numSource);
    }
    else
    {
        NumbEtape = 1;
    }


    std::ostringstream oss [NumbEtape];


    if (MemorySommet[numArivee][0] == -500)
    {
        BufferNum = numArivee;

        for (int J= int (NumbEtape -1); J >= 0; J--)
        {

            //Affichage premier sommet
            oss[J] << "[ " << m_tabSommets[MemorySommet[BufferNum][2]]->getNom() << " {" << m_tabSommets[MemorySommet[BufferNum][2]]->getNum()+1<< "} ]" ;


            //Affichage trajet emprunter entre les deux sommets
            oss[J] << "-- "<< m_tabTrajets[MemorySommet[BufferNum][3]]->getNom()<< " |" << m_tabTrajets[MemorySommet[BufferNum][3]]->getType() <<"| {" << m_tabTrajets[MemorySommet[BufferNum][3]]->getNum() + 1 << "} = "<< afficherSecondeEnTemps(transformerTempsEnSeconde(m_tabTrajets[MemorySommet[BufferNum][3]]->getTempsTrajet()))<<" -->";


            //Affichage deuxième sommet
            oss[J] << "[ " << m_tabSommets[BufferNum]->getNom() << " {" << m_tabSommets[BufferNum]->getNum() + 1 << "} ]  ,";

            BufferNum = MemorySommet[BufferNum][2];

        }

    }
    else
    {
        oss[0] << "Pas de chemin entre ces deux sommets";
    }

    while (exit_condition == 0)
    {
        blit(Ima2.TODO[42],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 110,makecol(255,255,255),-1,"CHEMIN MINIMIM DJIKSTRA de %s a %s : %s",MettreMajuscule(m_tabSommets[numSource]->getNom()).c_str(),MettreMajuscule(m_tabSommets[numArivee]->getNom()).c_str(),afficherSecondeEnTemps(SommeTotalDistance).c_str());

        for (int J= 0; J < NumbEtape; J++)
        {
            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 80 + (J) * 25,makecol(255,255,255),-1,MettreMajuscule(oss[J].str()).c_str());
        }


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }
}

void Graphe::affichResultatBFS(Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector <int> > memoryBFS,int BorneInferieur,int BorneSuperieur,int numSource,bool ArriveConnue, int numArrivee, bool Djikstra)
{
    // Variable exit condition
    int exit_condition = 0;

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

    //Vecteur de nom de d'options
    std::deque <std::string> VectorName;

    for (int I=0; I< int(memoryBFS.size()); I++)
    {
        std::ostringstream oss;

        oss << "CHEMIN VERS " << MettreMajuscule(m_tabSommets[I]->getNom()) << " ("<< m_tabSommets[I]->getNum() +1 <<") :";

        VectorName.push_back(oss.str().c_str());
    }

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


    //Buffercard Dimention
    int NombreDeChemin = BorneSuperieur - BorneInferieur - 1;


    int BuffCard_W = 444;
    int BuffCard_H =  5+ 67*NombreDeChemin + ( NombreDeChemin-1)* 8  +10;


    int BufferChoice = 100000; //On met un grand nombre pour que, si l'utilisateur n'a pas encore cliquer pour faire un
    // un choix, le choix dans le swich tout en bas se dirige vers l'option "default

    int BufferShowSommet = 0;

    BITMAP * BufferCard = NULL;
    BufferCard = create_bitmap(BuffCard_W,BuffCard_H);
    clear_bitmap(BufferCard);

    BITMAP * BufWindow = NULL;
    BufWindow = create_bitmap(BuffCard_W,402 - 90);
    clear_bitmap(BufWindow);


    while (exit_condition == 0)
    {
        blit(Ima2.TODO[40],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[9],(SCREEN_W - Ima2.TODO[9]->w)/2,(SCREEN_H - Ima2.TODO[9]->h)/2);
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[9]->h)/2 + 60,makecol(255,255,255),-1,"SOMMET DE DEPART : %s (%d)",m_tabSommets[numSource]->getNom().c_str(),m_tabSommets[numSource]->getNum()+1);

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
            BufferShowSommet = 0;

            // BuffAffiche = 0;
            for (int I= numArrivee; I< NombreDeChemin + numArrivee; I++)
            {

                if (I != numSource)
                {

                    rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(0,0,0,255));

                    //Condition pour cliquer sur l'option qu'on veut
                    if ((mouse_x>(SCREEN_W - Ima2.TODO[9]->w)/2 + 22)&&(mouse_x < (SCREEN_W - Ima2.TODO[9]->w)/2 + 22 + + BufWindow->w) && (mouse_y >  (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67)&&(mouse_y < (SCREEN_H - Ima2.TODO[9]->h)/2 +24 +67 + BufWindow->h))
                    {
                        if ((mouse_x>10 + (SCREEN_W - Ima2.TODO[9]->w)/2 + 27)&&(mouse_x < 10 + Ima2.TODO[10]->w +(SCREEN_W - Ima2.TODO[9]->w)/2 + 27) && (mouse_y > 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 +15 + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_y < 5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + Ima2.TODO[10]->h + (SCREEN_H - Ima2.TODO[37]->h)/2 + 10 - AvanceSlide)&&(mouse_b&1))
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
                        rectfill (BufferCard,10,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,10 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 + 67,makeacol(255,0,0,255));

                        BufferChoice = I;
                    }

                    rectfill (BufferCard,15,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15 +5,5 + Ima2.TODO[10]->w,5+ BufferShowSommet*67 +(BufferShowSommet-1)*8 + 10 + 67,makeacol(255,255,255,255));

                    textprintf_centre_ex(BufferCard,font,((BufferCard->w )/2),(67)/2 + BufferShowSommet*67 +(BufferShowSommet-1)*8 + 15,makecol(0,0,0),-1,VectorName[I].c_str());

                    BufferShowSommet++;


                }

            }
        }

        blit(BufferCard,BufWindow,0,AvanceSlide,0,0,BufWindow->w,BufWindow->h);
        draw_sprite (Ima2.page,BufWindow,(SCREEN_W - Ima2.TODO[9]->w)/2 + 27,(SCREEN_H - Ima2.TODO[37]->h)/2 + 10);


        if (NombreDeChemin>4)
        {
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

        }

        //Button accept
        ExitResponseAccept = acceptButton.activerButton(posButtonAccept_X,posButtonAccept_Y,Ima2.page,&buttonAccept_condition,&sound_ConditionAccept,Music);
        if ( ExitResponseAccept == true )
        {
            if ((BufferChoice>=0)&&(BufferChoice< int(VectorName.size())))
            {
                if (Djikstra == false)
                {
                    affichBFSTrajet(Ima2,Samp4,Music,memoryBFS,numSource,BufferChoice);
                }
                else
                {
                    affichDjikstraTrajet(Ima2,Samp4,Music,memoryBFS,numSource,BufferChoice);
                }

            }

        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(Ima2.page,Ima2.BuffpageAvant,0,0,0,0,SCREEN_W,SCREEN_H);

    }

    destroy_bitmap(BufferCard);
    destroy_bitmap(BufWindow);

}

void Graphe::affichBFSTrajet(Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector <int> > memoryBFS, int numSource, int numArivee)
{

    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (0);
    int posButtonExit_X = 20,posButtonExit_Y = 20;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;


    int BufferNum = 0;
    int NumbEtape = 0;

    if (memoryBFS[numArivee][0] == -500)
    {
        //On trouve le nombre d'etape pour passer du sommet de depart à celui d'arriver
        BufferNum = numArivee;
        do
        {
            BufferNum = memoryBFS[BufferNum][1];

            NumbEtape++;
        }
        while(BufferNum != numSource);
    }
    else
    {
        NumbEtape = 1;
    }

    std::ostringstream oss [NumbEtape];

    if (memoryBFS[numArivee][0] == -500)
    {
        BufferNum = numArivee;

        for (int J= int (NumbEtape -1); J >= 0; J--)
        {

            //Affichage premier sommet
            oss[J] << "[ " << m_tabSommets[memoryBFS[BufferNum][1]]->getNom() << " {" << m_tabSommets[memoryBFS[BufferNum][1]]->getNum()+1<< "} ]" ;


            //Affichage trajet emprunter entre les deux sommets
            oss[J] << "-- "<< m_tabTrajets[memoryBFS[BufferNum][2]]->getNom()<< " |" << m_tabTrajets[memoryBFS[BufferNum][2]]->getType() <<"| {" << m_tabTrajets[memoryBFS[BufferNum][2]]->getNum() + 1 << "} -->";


            //Affichage deuxième sommet
            oss[J] << "[ " << m_tabSommets[BufferNum]->getNom() << " {" << m_tabSommets[BufferNum]->getNum() + 1 << "} ]  ,";

            BufferNum = memoryBFS[BufferNum][1];

        }

    }
    else
    {


        oss[0] << "Pas de chemin reliant ces deux sommets";
    }



    while (exit_condition == 0)
    {
        blit(Ima2.TODO[42],Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 110,makecol(255,255,255),-1,"CHEMIN MINIMIM BFS de %s a %s :",MettreMajuscule(m_tabSommets[numSource]->getNom()).c_str(),MettreMajuscule(m_tabSommets[numArivee]->getNom()).c_str());

        for (int J= 0; J < NumbEtape; J++)
        {
            textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H)/2 - 80 + (J) * 25,makecol(255,255,255),-1,MettreMajuscule(oss[J].str()).c_str());
        }


        ExitResponse = exitButton.activerButton(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

    }


}



void Graphe::BFS(Images Ima2, samples  Samp4, sound * Music)
{
    int sommet1 = 10000;
    bool decision = false;

    std::queue <int> FileBFS;
    std::vector <std::vector <int> > memoryBFS (m_tabSommets.size(),std::vector <int> (1,-100)); // -100 signifie non découvert ici

    int BufferNum = 0;

    std::deque <int> BufferChemin;
    std::deque <int> BufferTrajet;

    //Programme pour choisir le sommet de depart du BFS
    decision = choixUnSommet(sommet1,Ima2,Samp4,Music);

    // std::cout << sommet1 << std::endl;

    if (decision == false)
    {
        //On pousse le premié sommet dans la file
        FileBFS.push(sommet1);

        //On le marque comme decouvert
        memoryBFS[FileBFS.front()][0] = - 500; // -500 ici signifiera sommet découvert

        //On remet tout les flots a "0" de base pour un flot nul pour reutiliser le BFS des flots
        for (const auto& elem : m_tabTrajets)
        {
            elem->setFlot(0);
        }

        while (FileBFS.empty() == false)
        {

            //std::cout << "AAA ";

            // On met les adjacences dans la file, et on garde en memoire qui est l'antécedent des nouveux sommets
            m_tabSommets[FileBFS.front()]->donnerAdjacenceBFS(FileBFS,memoryBFS);

            //std::cout << "BBB" << std::endl;

            //On enleve le sommet devant la file, tout ces successeurs on été découvert
            FileBFS.pop();

        }

        system("CLS");


        //Affichage en mode console
        for (int I=0; I< int(m_tabSommets.size()); I++)
        {
            if (memoryBFS[I][0] == -500) // Le sommet choisi au debut est forcément pas pris en compte, vue qu'il n'a pas de sommet
            {
                if (I != sommet1)
                {
                    // qui la decouvert
                    std::cout << I;

                    BufferNum = I;
                    do
                    {
                        BufferNum = memoryBFS[BufferNum][1];

                        std::cout << " <-- ";

                        std::cout << BufferNum;

                    }
                    while(BufferNum != sommet1);

                    std::cout << std::endl;
                }

            }
        }

        //Affichage des resultats en mode graphique
        affichResultatBFS(Ima2,Samp4,Music,memoryBFS,-1,37,sommet1,false,0,false);

    }

}
