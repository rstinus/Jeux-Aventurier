#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
#include "Objet.h"
#include "Niveau.h"
using namespace std;

// Constructeur
Niveau::Niveau(Image& image, string nomf, Dictionnaire& dico) {
    ifstream entree;
    entree.open(nomf);
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
        entree >> nom >> x >> y;
        Objet o(image, nom, dico, x*16, y*16);
        _decor.push_back(o);
    }
    entree.close();

    _bonus = nbBonus();
}

// Dessiner le décor
void Niveau::dessiner() {
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() != "cache") {
            _decor.at(i).dessiner();
        }
    }
}

// Vérifié si le personnage peut avancer
bool Niveau::caseEtLibre(int posX, int posY) {
    bool caselibre = true;
    int indice = indiceObjet(posX, posY, "solide");
    if (indice != -1) {
        caselibre = false;
    }
    return caselibre;
}

// Calcul le nombre de bonus présent dans le niveau
int Niveau::nbBonus() {
    int bonus=0;
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() == "bonus") {
            bonus++;
        }
    }
    return bonus;
}

// Tester si un bonus est présent sur la case courante et si oui le récupéré
void Niveau::testerBonusEtPrendre(int posX, int posY) {
    int indice = indiceObjet(posX, posY, "bonus");
    if (indice != -1){
        _bonus -= 1;
        _decor.at(indice).cache();
    }
}

// Vérifie si le joueur a gagné
bool Niveau::gagne() {
    bool gagner = false;
    if (_bonus == 0) {
        gagner = true;
    }
    return gagner;
}

// Sous fonction pour caseEtLibre et testerBonusEtPrendre
int Niveau::indiceObjet(int x, int y, string prop) {
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() == prop) {
            if ( (x == _decor.at(i).getX()) && (y == _decor.at(i).getY()) ) {
                return i;
            }
        }
    }
    return -1;
}
