#include "Graphe.h"

// constructeur par défaut
Trajet::Trajet()
    : m_num(-1), m_nom("no name"), m_type("no type"), m_tempsTrajet(std::make_pair(-1, -1)), m_extremites(std::make_pair(nullptr, nullptr)), m_capacity(0),m_flot(0)
{}

// constructeur surchargé
Trajet::Trajet(int num, const std::string &nom, const std::string &type, Sommet* depart, Sommet* arrivee, Donnee data, bool GrapheEcart)
    : m_capacity(0),m_flot(0)
{
    m_num = num;
    m_nom = nom;
    m_type = type;
    m_extremites = std::make_pair(depart, arrivee);

    // initialisation du temps du trajet
    // le temps de trajet dépend du moyen de déplacement (téléphérique, bus, type de piste etc)
    int tempsSeconde, denivele;

    // si c'est une remontée
    if(m_extremites.first->getAltitude() - m_extremites.second->getAltitude() < 0)
    {
        if(m_type == "BUS")
        {
            if((m_nom == "navette1600-2000") || ((m_nom == "navette2000-1600")))
            {
                m_tempsTrajet = std::make_pair(data.BUS_info[1], 0);
            }
            if((m_nom == "navette1600-1800") || ((m_nom == "navette1800-1600")))
            {
                m_tempsTrajet = std::make_pair(data.BUS_info[2], 0);
            }

            m_capacity = data.BUS_info[0];
        }
        if(m_type == "TPH")
        {
            denivele = m_extremites.second->getAltitude() - m_extremites.first->getAltitude();
            tempsSeconde = int(data.TPH_info[3] + (float(data.TPH_info[1])/float(data.TPH_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.TPH_info[0];
        }
        if(m_type == "TC")
        {
            denivele = m_extremites.second->getAltitude() - m_extremites.first->getAltitude();
            tempsSeconde = int(data.TC_info[3] + (float(data.TC_info[1])/float(data.TC_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.TC_info[0];
        }
        if(m_type == "TSD")
        {
            denivele = m_extremites.second->getAltitude() - m_extremites.first->getAltitude();
            tempsSeconde = int(data.TSD_info[3] + (float(data.TSD_info[1])/float(data.TSD_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.TSD_info[0];
        }
        if(m_type == "TS")
        {
            denivele = m_extremites.second->getAltitude() - m_extremites.first->getAltitude();
            tempsSeconde = int(data.TS_info[3] + (float(data.TS_info[1])/float(data.TS_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.TS_info[0];
        }
        if(m_type == "TK")
        {
            denivele = m_extremites.second->getAltitude() - m_extremites.first->getAltitude();
            tempsSeconde = int(data.TK_info[3] + (float(data.TK_info[1])/float(data.TK_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.TK_info[0];
        }
    }
    // si c'est une descente
    if(m_extremites.first->getAltitude() - m_extremites.second->getAltitude() > 0)
    {
        if(m_type == "BUS")
        {
            if((m_nom == "navette1600-2000") || ((m_nom == "navette2000-1600")))
            {
                m_tempsTrajet = std::make_pair(data.BUS_info[1], 0);
            }
            if((m_nom == "navette1600-1800") || ((m_nom == "navette1800-1600")))
            {
                m_tempsTrajet = std::make_pair(data.BUS_info[2], 0);
            }

            m_capacity = data.BUS_info[0];
        }
        if(m_type == "V")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.V_info[1])/float(data.V_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.V_info[0];
        }
        if(m_type == "B")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.B_info[1])/float(data.B_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.B_info[0];
        }
        if(m_type == "R")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.R_info[1])/float(data.R_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60 , tempsSeconde % 60);

            m_capacity = data.R_info[0];

        }
        if(m_type == "N")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.N_info[1])/float(data.N_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.N_info[0];
        }
        if(m_type == "KL")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.KL_info[1])/float(data.KL_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.KL_info[0];
        }
        if(m_type == "SURF")
        {
            denivele = m_extremites.first->getAltitude() - m_extremites.second->getAltitude();
            tempsSeconde = int((float(data.SURF_info[1])/float(data.SURF_info[2])) * denivele);
            m_tempsTrajet = std::make_pair((tempsSeconde - (tempsSeconde % 60))/60, tempsSeconde % 60);

            m_capacity = data.SURF_info[0];
        }
    }

    if (GrapheEcart == true)
    {
        m_capacity = 1000000;
    }
}


Trajet::~Trajet()
{}

// affichage en mode graphique des infos du trajet
void Trajet::afficherInfo(Images Ima2, samples  Samp4, sound * Music,BITMAP* background)
{

    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (2);
    int posButtonExit_X = 610,posButtonExit_Y = 80;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    while (exit_condition == 0)
    {
        blit(background,Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //On noicit l'ecran de derrière
        rectfill (Ima2.page,0,0,SCREEN_W,SCREEN_H,makeacol(0,0,0,150));


        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[37],(SCREEN_W - Ima2.TODO[37]->w)/2,(SCREEN_H - Ima2.TODO[37]->h)/2);

        std::ostringstream oss;

        oss << "Nom du trajet numero "<<m_num+1 << " : " ;

        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[2]->h)/2 + 60 + 35,makecol(255,255,255),-1,MettreMajuscule(oss.str()).c_str());

        std::ostringstream oss2;

        oss2 << MettreMajuscule(m_nom) ;
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 35,makecol(255,0,0),-1,oss2.str().c_str());


        std::ostringstream oss3;

        oss3 << "Type de trajet : " ;

        if ("V" == m_type)
        {
            oss3 << "Piste verte [" << m_type << "]";
        }

        if ("B" == m_type)
        {
            oss3 << "Piste bleu [" << m_type << "]";
        }

        if ("R" == m_type)
        {
            oss3 << "Piste rouge [" << m_type << "]";
        }

        if ("N" == m_type)
        {
            oss3 << "Piste noire [" << m_type << "]";
        }


        if ("KL" == m_type)
        {
            oss3 << "Piste de kilometre lance [" << m_type << "]";
        }


        if ("SURF" == m_type)
        {
            oss3 << "Snowpark [" << m_type << "]";
        }


        if ("TPH" == m_type)
        {
            oss3 << "Telepherique [" << m_type << "]";
        }


        if ("TC" == m_type)
        {
            oss3 << "Telecabine [" << m_type << "]";
        }


        if ("TSD" == m_type)
        {
            oss3 << "Telesiege debrayable [" << m_type << "]";
        }


        if ("TS" == m_type)
        {
            oss3 << "Telesiege [" << m_type << "]";
        }

        if ("TK" == m_type)
        {
            oss3 << "Teleski [" << m_type << "]";
        }

        if ("BUS" == m_type)
        {
            oss3 << "Navette [" << m_type << "]";
        }


        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 75,makecol(255,255,255),-1,oss3.str().c_str());
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 75,makecol(255,255,0),-1,"Type de trajet : ");


        std::ostringstream oss4;

        oss4 << "Duree du trajet : " << m_tempsTrajet.first << " minute(s) et " << m_tempsTrajet.second << " second(s)";

        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 110,makecol(255,255,255),-1,oss4.str().c_str());
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 110,makecol(255,255,0),-1,"Duree du trajet : ");


        std::ostringstream oss5;

        if (m_extremites.first->getAltitude() - m_extremites.second->getAltitude() >= 0)
        {
            oss5 << "Denivele : " << m_extremites.first->getAltitude() - m_extremites.second->getAltitude() << " m";
        }
        else
        {
            oss5 << "Denivele : " << m_extremites.second->getAltitude() - m_extremites.first->getAltitude() << " m";
        }


        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 145,makecol(255,255,255),-1,oss5.str().c_str());
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 145,makecol(255,255,0),-1,"Denivele : ");


        std::ostringstream oss6;

        oss6 << "Depart : " << m_extremites.first->getNom() << " ("<< m_extremites.first->getNum() +1<< ") "  ;

        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 180,makecol(255,255,255),-1,oss6.str().c_str());
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 180,makecol(255,255,0),-1,"Depart : ");

        std::ostringstream oss7;

        oss7 << "Arrivee : " << m_extremites.second->getNom() <<" (" <<m_extremites.second->getNum() +1<< ") ";

        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 215,makecol(255,255,255),-1,oss7.str().c_str());
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 200,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 215,makecol(255,255,0),-1,"Arrivee : ");


        ExitResponse = exitButton.activerButtonCercle(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }

}

// getter pour les attributs de la classe Trajet
int Trajet::getNum() const {return m_num;}
const std::string &Trajet::getNom() const {return m_nom;}
const std::pair<Sommet *, Sommet *> &Trajet::getExtremites() const {return m_extremites;}
const std::string &Trajet::getType() const {return m_type;}
std::pair<int, int> Trajet::getTempsTrajet() const {return m_tempsTrajet;}
int Trajet::getCapacity() const {return m_capacity;}
int Trajet::getFlot() const {return m_flot;}

// setter pour les attributs de la classe Trajet
void Trajet::setFlot(int flot)
{
    m_flot = flot;
}

void Trajet::setNum(int Num)
{
    m_num = Num;
}

void Trajet::setCapacity(int capacity)
{
    m_capacity = capacity;
}

