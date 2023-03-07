#include "Graphe.h"

// constructeur par défaut
Sommet::Sommet()
    : m_num(-1), m_nom("no name"), m_altitude(-1)
{
}

// constructeur surchargé
Sommet::Sommet(int num, const std::string &nom, int altitude)
    :   m_num (num), m_nom (nom), m_altitude (altitude)
{
}

// destructeur
Sommet::~Sommet()
{
}

// getter pour les attributs de la classe Sommet
int Sommet::getNum() const {return m_num;}
const std::string &Sommet::getNom() const {return m_nom;}
int Sommet::getAltitude() const {return m_altitude;}
const std::vector<Trajet *> &Sommet::getTrajets() const {return m_trajets;}
std::vector<std::pair<Sommet *, int>> Sommet::getSuccesseurs() const {return m_successeurs;}

// setter pour le tableau de trajet
void Sommet::setTrajets(Trajet* newTrajet)
{
    m_trajets.push_back(newTrajet);
}

void Sommet::deleteTrajet(int NumTrajet)
{
    for (int I =0; I< int(m_trajets.size()); I++)
    {
        if (m_trajets[I]->getNum() == NumTrajet)
        {

        m_trajets.erase(m_trajets.begin() + I);
        break;
        }
    }
}

// settre pour les successeurs du sommet
void Sommet::setSuccesseurs(Sommet* voisin, std::pair<int, int> temps)
{
    int tempsSeconde = 60 * temps.first + temps.second;
    m_successeurs.emplace_back(voisin, tempsSeconde);
}

// affichage graphique des infos du sommet
void Sommet::afficherInfo (Images Ima2, samples  Samp4, sound * Music,BITMAP* background)
{
    // Variable exit condition
    int exit_condition = 0;

    //Button Exit condition
    Button exitButton (2);
    int posButtonExit_X = 610,posButtonExit_Y = 80;
    int buttonExit_condition = 0;
    int sound_Condition1 = 1;
    bool ExitResponse = false;

    int nbTrajetRentrant = 0;
    int nbTrajetSortant = 0;


    while (exit_condition == 0)
    {
        blit(background,Ima2.page,0,0,0,0,SCREEN_W,SCREEN_H);

        //On noicit l'ecran de derrière
        rectfill (Ima2.page,0,0,SCREEN_W,SCREEN_H,makeacol(0,0,0,150));


        //Affichage panneau de derriere
        draw_sprite (Ima2.page,Ima2.TODO[37],(SCREEN_W - Ima2.TODO[37]->w)/2,(SCREEN_H - Ima2.TODO[37]->h)/2);

        std::ostringstream oss;

        oss << "Nom du sommet numero "<<m_num+1 << " : " ;

        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[2]->h)/2 + 60 + 35,makecol(255,255,255),-1,MettreMajuscule(oss.str()).c_str());

        std::ostringstream oss2;

        oss2 << MettreMajuscule(m_nom) << " (" << m_altitude << " m )";
        textprintf_centre_ex(Ima2.page,font,(SCREEN_W )/2,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 35,makecol(255,0,0),-1,oss2.str().c_str());

        nbTrajetRentrant = 0;
        nbTrajetSortant = 0;

        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 140 - 60,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 100 - 25,makecol(255,255,0),-1,"Pistes rentrante :");
        textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 140 +180,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 100 - 25,makecol(255,255,0),-1,"Pistes sortante :");


        for (int I=0; I< int(m_trajets.size()); I++)
        {
            //Si trajet sortant du sommet
            if (m_trajets[I]->getExtremites().first->getNum() == m_num)
            {
                std::ostringstream oss3;

                oss3 << "(" << m_trajets[I]->getNum()+1 << ") " << m_trajets[I]->getNom() << " [" << m_trajets[I]->getType() << "]";
                textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 140 +170,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 100 + 17* nbTrajetSortant,makecol(255,255,255),-1,oss3.str().c_str());

                nbTrajetSortant++;

            }
            else
            {
                //Sinon c'est un trajet entrant dans le sommet

                std::ostringstream oss3;

                oss3 << "(" << m_trajets[I]->getNum()+1 << ") " << m_trajets[I]->getNom() << " [" << m_trajets[I]->getType() << "]";
                textprintf_ex(Ima2.page,font,(SCREEN_W )/2 - 140 - 70,(SCREEN_H - Ima2.TODO[2]->h)/2 + 80 + 100 + 17* nbTrajetRentrant,makecol(255,255,255),-1,oss3.str().c_str());

                nbTrajetRentrant++;

            }

        }


        ExitResponse = exitButton.activerButtonCercle(posButtonExit_X,posButtonExit_Y,Ima2.page,&buttonExit_condition,&sound_Condition1,Music);
        if ( ExitResponse == true )
        {
            exit_condition = 1;
        }

        blit(Ima2.page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}


// Methode pour faire le travail de decouverte d'un sommets pour le parcour BFS
void Sommet::donnerAdjacenceBFS(std::queue <int>& FileBFS2,std::vector <std::vector <int>>& memoryBFS2)
{
    // std::cout <<" PK " << FileBFS2.front() << " " << m_trajets.size() <<std::endl;

    for (const auto& elem : m_trajets)
    {
        if(elem->getFlot() < elem->getCapacity())
        {
            if (elem->getExtremites().first->getNum() == m_num)
            {

                // Si le Sommet de l'adacence n'a pas encore été découvert...
                if (memoryBFS2[elem->getExtremites().second->getNum()][0]!= -500)
                {
                    // ...On le met dans la file
                    FileBFS2.push(elem->getExtremites().second->getNum());

                    //On le qualifie de découvert
                    memoryBFS2[elem->getExtremites().second->getNum()][0]= -500;

                    //On garde en memoire qui la découvert
                    memoryBFS2[elem->getExtremites().second->getNum()].push_back(FileBFS2.front());

                    //On garde en memoire qui le numero du trajet qui la decouvert
                    memoryBFS2[elem->getExtremites().second->getNum()].push_back(elem->getNum());
                }
            }
        }
    }
}

void Sommet::donnerAdjacenceBFSGraphEcart(std::queue <int>& FileBFS2,std::vector <std::vector <int>>& memoryBFS2)
{
    for (const auto& elem : m_trajets)
    {
        if(((elem->getCapacity() == 1000000)&&(elem->getFlot() != 0))||((elem->getCapacity() != 1000000)&&( elem->getFlot() < elem->getCapacity())))
        {
            if (elem->getExtremites().first->getNum() == m_num)
            {

                // Si le Sommet de l'adacence n'a pas encore été découvert...
                if (memoryBFS2[elem->getExtremites().second->getNum()][0]!= -500)
                {
                    // ...On le met dans la file
                    FileBFS2.push(elem->getExtremites().second->getNum());

                    //On le qualifie de découvert
                    memoryBFS2[elem->getExtremites().second->getNum()][0]= -500;

                    //On garde en memoire qui la découvert
                    memoryBFS2[elem->getExtremites().second->getNum()].push_back(FileBFS2.front());

                    //On garde en memoire qui le numero du trajet qui la decouvert
                    memoryBFS2[elem->getExtremites().second->getNum()].push_back(elem->getNum());
                }
            }
        }
    }

}


void Sommet::AdjacenceDjikstra(std::priority_queue <std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int> >,comparaison>& filePriority,std::vector <std::vector<int> >& MemorySommet)
{
    std::pair <Sommet*,int> BufferPaire;

    // On definit le sommet sortant actuel de la file de priorité comme totalement exploré avec la valeur "-500"
    // Pas de problème en cas d'un sommet mis à jour et donc present deux fois dans la file de priorité, car le sommet
    // mis a jour aura forcement une distance plus petite que son ancienne version, il sera donc traité avant l'ancienne
    // version, et donc mis à "-500" au bon moment
    MemorySommet[filePriority.top().first->getNum()][0] = -500;

    // On fait un buffer du sommet sortant de la file
    BufferPaire = filePriority.top();
    filePriority.pop();

    //Si le sommet sortant de la file n'a pas subit de modification (de distance notamment) entre temps, on effectue
    //bien le traiment du sommet
    if (BufferPaire.second == MemorySommet[m_num][1])
    {
        // std::cout << "KKK ";
        for (const auto& elem : m_trajets)
        {
            //std::cout << "LLL " << elem->getExtremites().first->getNum() << " ";
            //   std::cout << "MMM ";


            if(elem->getFlot() < elem->getCapacity())
            {
                if (elem->getExtremites().first->getNum() == m_num)
                {

                    if (MemorySommet[elem->getExtremites().second->getNum()][0] != -500)// Si le sommet n'est pas encore exploré
                    {
                        //Si le sommet adjacent a une distance enregistré plus élevé que celle que propose le sommet actuel
                        //(donc chemin plus cour possible), ou si la distance est de zero
                        if ((MemorySommet[elem->getExtremites().second->getNum()][1] > MemorySommet [m_num][1] + transformerTempsEnSeconde(elem->getTempsTrajet()))||(MemorySommet[elem->getExtremites().second->getNum()][1] == 0))
                        {
                            //On donne sa distance du sommet de depart
                            MemorySommet [elem->getExtremites().second->getNum()][1] = MemorySommet [m_num][1] + transformerTempsEnSeconde(elem->getTempsTrajet());

                            //On garde en memoire le sommet qui la decouvert
                            MemorySommet [elem->getExtremites().second->getNum()][2] = this->getNum();

                            //On les remets dans la priorityQueue
                            filePriority.push(std::make_pair(elem->getExtremites().second,MemorySommet [elem->getExtremites().second->getNum()][1] ));

                            //On garde en memoire le numero de trajet qui la decouvert
                            MemorySommet [elem->getExtremites().second->getNum()][3] = elem->getNum();

                        }

                    }
                }
            }
        }

        //  std::cout << "DDD ";

    }


}

// calcule du temps pour aller du sommet à un de ses voisins
int Sommet::DistanceAdjacence(int NumSommetAdjacence)
{
    int ValeurDistance = 0;

    for (const auto& elem :m_trajets)
    {
        if (elem->getExtremites().first->getNum() == m_num)
        {
            if (elem->getExtremites().second->getNum() == NumSommetAdjacence)
            {
                ValeurDistance = transformerTempsEnSeconde(elem->getTempsTrajet());

            }
        }
    }

    return ValeurDistance;
}
