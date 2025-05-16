#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
using namespace std;

// Constructeur
Dictionnaire::Dictionnaire() {
    string nom = "./assets/dictionnaire.txt";
    ifstream entree;
    entree.open(nom);
    if (!(entree.is_open())) {
        throw string ("Dictionnaire.txt n'est pas ouvert");
    }
    int nbInt;
    if (!(entree.eof())) {
        entree >> nbInt;
    }
    for (int i=0; i<nbInt && !entree.eof(); i++) {
        string nom;
        int x;
        int y;
        string prop;
        entree >> nom >> x >> y >> prop;
        Tuile t(nom, x, y, prop);
        _LesTuiles.push_back(t);
    }
    entree.close();
}

// Afficher le contenu du vecteur
void Dictionnaire::afficher() const{
    for (int i=0; i<_LesTuiles.size(); i++) {
        _LesTuiles.at(i).afficher();
    }
}

// Question 8 : l'algorithme de recherche utilisé et une recherche dichotomique
bool Dictionnaire::recherche(string nom, Tuile& chercher) const {
    int milieu;
    int debut = 0;
    int fin = _LesTuiles.size()-1;
    bool trouve = false;

    while (!trouve && debut <= fin)
    {
        milieu = (debut + fin) / 2;
        trouve = (_LesTuiles.at(milieu).getNom() == nom);

            if (_LesTuiles.at(milieu).getNom() > nom)
            {
                fin = milieu - 1;
            }
            else
            {
                debut = milieu + 1;
            }
        }
    chercher = _LesTuiles.at(milieu);
    return trouve;
}
