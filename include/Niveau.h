#ifndef NIVEAU_H_INCLUDED
#define NIVEAU_H_INCLUDED
#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
#include "Objet.h"
using namespace std;

class Niveau {
    vector<Objet> _decor;
    int _bonus;
public :
    Niveau(Image& image, string nomf, Dictionnaire& dico);

    void dessiner();

    bool caseEtLibre(int posX, int posY);

    int nbBonus();

    void testerBonusEtPrendre(int posX, int posY);

    bool gagne();

    int indiceObjet(int x, int y, string prop);
};

#endif // NIVEAU_H_INCLUDED
