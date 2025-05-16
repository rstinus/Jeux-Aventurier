#ifndef DICTIONNAIRE_H_INCLUDED
#define DICTIONNAIRE_H_INCLUDED
#include "Image.h"
#include <string>
#include "Moteur.h"
#include <vector>
#include "Tuile.h"
#include <fstream>
using namespace std;

class Dictionnaire {
    vector<Tuile> _LesTuiles;
public:

    Dictionnaire();

    void afficher() const ;

    bool recherche(string nom, Tuile& chercher) const;
};


#endif // DICTIONNAIRE_H_INCLUDED
