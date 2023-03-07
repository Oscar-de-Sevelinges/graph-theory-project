#ifndef SOMMETS_H_INCLUDED
#define SOMMETS_H_INCLUDED

///Personal Libraries
#include "Graphe.h"
#include "Trajet.h"
#include "Library.h"

///Class

class Trajet;

struct Images;

struct samples;

struct sound;


//Fonction de comparaison de la priorityQueue
struct comparaison
{
    bool operator()(std::pair<Sommet*,int> a,std::pair<Sommet*,int> b)
    {
        return (a.second >= b.second);
    }
};

class Sommet
{
private:

    // un sommet est composé d'un numéro
    //                       d'un nom
    //                       d'une altitude
    //                       d'un vecteur de pointeur trajet
    //                    et d'un vecteur de pair de Sommet et d'entier, contenant le sommet voisin et la distance entre les deux
    int m_num;
    std::string m_nom;
    int m_altitude;
    std::vector<Trajet*> m_trajets;
    std::vector<std::pair<Sommet*, int>> m_successeurs;

public:

    ///Constructeur
    Sommet();
    Sommet(int num, const std::string &nom, int altitude);

    ///Destructeur
    ~Sommet();

    ///Methodes
    // affichage des infos du sommet
    void afficherInfo (Images Ima2, samples  Samp4, sound * Music,BITMAP* background);

    void donnerAdjacenceBFS(std::queue <int>& FileBFS2,std::vector <std::vector <int>>& memoryBFS2);
    void donnerAdjacenceBFSGraphEcart(std::queue <int>& FileBFS2,std::vector <std::vector <int>>& memoryBFS2);

    void AdjacenceDjikstra(std::priority_queue <std::pair<Sommet*,int>,std::vector<std::pair<Sommet*,int> >,comparaison>& filePriority,std::vector <std::vector<int> >& MemorySommet);
    // calcule du temps entre 2 sommets voisins
    int DistanceAdjacence(int NumSommetAdjacence);

    ///Accesseurs

    int getNum() const;
    const std::string &getNom() const;
    int getAltitude() const;
    const std::vector<Trajet *> &getTrajets() const;
    void setTrajets(Trajet* newTrajet);

    void deleteTrajet (int NumTrajet);

    std::vector<std::pair<Sommet*, int>> getSuccesseurs() const;
    void setSuccesseurs(Sommet* voisin, std::pair<int, int> temps);

};

#endif // SOMMETS_H_INCLUDED
