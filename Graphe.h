#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED


///Libraries
#include <fstream>
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <queue>
#include <deque>

///Personal Libraries
#include "Sommets.h"
#include "Trajet.h"
#include "Library.h"

///Constants
#define nbInfo 3


///Structure
struct Donnee
{
    //Donnée pour les remontée
    int TPH_info[nbInfo+1];
    int TC_info[nbInfo+1];
    int TSD_info[nbInfo+1];
    int TS_info[nbInfo+1];
    int TK_info[nbInfo+1];
    int BUS_info[nbInfo+1];

    //Donnée pour les pistes
    int V_info[nbInfo];
    int B_info[nbInfo];
    int R_info[nbInfo];
    int N_info[nbInfo];
    int KL_info[nbInfo];
    int SURF_info[nbInfo];

};

///Class

class Graphe
{
private:
    // un graphe est constituée d'un tableau de pointeur sur Trajet,
    //                          d'un tableau de pointeur sur Sommet,
    //                          d'une structure Donnee
    std::vector<Trajet*> m_tabTrajets;
    std::vector<Sommet*> m_tabSommets;

    Donnee m_data;

public:
    //Constructeur
    explicit Graphe(const std::string& nomFichier, bool GrapheEcart);

    //Destructeur
    ~Graphe();

    // choix du trajet pour afficher ses infos
    void choixTrajet(Images Ima2, samples  Samp4, sound * Music) const;
    // choix du sommet pour afficher ses infos
    void choixSommet(Images Ima2, samples  Samp4, sound * Music)  const;

    bool choixDeuxSommet (int& sommet1,int& sommet2,Images Ima2, samples  Samp4, sound * Music, bool Sommet2True);
    bool choixUnSommet (int& sommet1,Images Ima2, samples  Samp4, sound * Music);


    //Methodes pour l'etude des flots (4.6)
    void etudeFlotMax(Images Ima2, samples  Samp4, sound * Music);
    void FlotMaxGrapheEcart(Images Ima2, samples  Samp4, sound * Music);
    bool parcourBFS(int NumSommetDepart, int NumSommetArrive,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >&memoryTotal);
    bool parcourBFSGrapheEcart(int NumSommetDepart, int NumSommetArrive,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >&memoryTotal);
    void afficherResultFlot(Images Ima2, samples  Samp4, sound * Music,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >memoryTotal,int numSource, int numPuit);
    void afficherResultChemin (Images Ima2, samples  Samp4, sound * Music,std::vector <std::pair<std::pair <int, std::deque <int> >,std::deque <int>  > >memoryTotal, int place, bool BufferToPlace);
    void modifValFlot (Images Ima2, samples  Samp4, sound * Music);

    void bufferParcour(Images Ima2, samples  Samp4, sound * Music,bool UnOuDeux);

    // methode pour le parcours du graphe (4.3)
    void BFS(Images Ima2, samples  Samp4, sound * Music) ;
    void BFS2(Images Ima2, samples  Samp4, sound * Music) ;
    void affichResultatBFS(Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector <int> > memoryBFS,int BorneInferieur,int BorneSuperieur,int numSource,bool ArriveConnue, int numArrivee, bool Djikstra);
    void affichBFSTrajet (Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector <int> > memoryBFS, int numSource, int numArivee);
    void dijkstraTemps(Images Ima2, samples  Samp4, sound * Music,bool UnDeux) ;
    void affichDjikstraTrajet (Images Ima2, samples  Samp4, sound * Music,std::vector <std::vector<int>> MemorySommet , int numSource, int numArivee);

    // sous-programme pour trajets perso (4.5)
    void modifValPreference (Images Ima2, samples  Samp4, sound * Music);
    void appliquerPreference ();

    //Accesseurs
    const std::vector<Trajet *> &getTabTrajets() const;
    const std::vector<Sommet*> &getTabSommets() const;

    void setTabTrajets(Trajet* nouveauTrajet);
    void setTabSommets(Sommet* nouveauSommet);

    // opérateur << pour afficher un graphe
    friend std::ostream &operator<<(std::ostream &os, const Graphe &graphe);
};



#endif // GRAPHE_H_INCLUDED
