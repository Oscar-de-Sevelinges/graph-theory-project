#ifndef TRAJET_H_INCLUDED
#define TRAJET_H_INCLUDED


///Personal Libraries
#include "Graphe.h"
#include "Sommets.h"
#include "Library.h"

///Class

class Sommet;

struct Donnee;

struct Images;

struct samples;

struct sound;

class Trajet
{
private:
    // un trajet est composé d'un numéro,
    //                       d'un nom,
    //                       d'un type,
    //                       d'une paire contenant le temps sous la forme x minute(s) et y seconde(s)
    //                       d'une capacité
    //                    et d'un flot
    int m_num;
    std::string m_nom;
    std::string m_type;
    std::pair<int, int> m_tempsTrajet;
    std::pair<Sommet*, Sommet*> m_extremites;
    int m_capacity;
    int m_flot;

public:

    ///Constructeur
    Trajet();
    Trajet(int num, const std::string &nom, const std::string &type, Sommet* depart, Sommet* arrivee, Donnee data, bool GrapheEcart);

    ///Destructeur
    ~Trajet();


    ///Methodes
    // affichage en mode graphique des infos du trajet
    void afficherInfo (Images Ima2, samples  Samp4, sound * Music,BITMAP* background);

    ///Accesseurs
    const std::string &getType() const;
    std::pair<int, int> getTempsTrajet() const;
    int getNum() const;
    void setNum (int Num);
    const std::string &getNom() const;
    const std::pair<Sommet *, Sommet *> &getExtremites() const;
    int getCapacity () const;
    void setCapacity(int capacity);
    int getFlot () const;
    void setFlot (int flot);
};


#endif // TRAJET_H_INCLUDED
