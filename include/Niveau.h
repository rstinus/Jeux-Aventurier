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
    vector<bool> _ramasses;
    int _bonus;
    int _niveauCurent;
    string _nomFichier;
    Image _image;
    Dictionnaire _dico;
public :
    Niveau(Image& image, string nomf, Dictionnaire& dico);

    void dessiner();

    bool caseEtLibre(int posX, int posY);

    int nbBonus();

    void testerBonusEtPrendre(int posX, int posY);

    bool gagne();

    int indiceObjet(int x, int y, string prop);

    int getBonus();

    void setNiveau(const std::string& nomf, Dictionnaire& dico);

    int getNiveauCurent();

    void setNiveauCurrent(const std::string& nomf);

    void chargerNiveau(int numero, Dictionnaire& dico);

};

#endif // NIVEAU_H_INCLUDED
