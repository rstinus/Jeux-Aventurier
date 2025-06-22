#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
#include "Objet.h"
#include "Niveau.h"
#include <regex>
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

    _ramasses.clear();
    _ramasses.resize(_decor.size(), false);


    _bonus = nbBonus();

    _nomFichier = nomf;

    _image = image;

    _niveauCurent = 1;
}

// Dessiner le d�cor
void Niveau::dessiner() {
    for (size_t i = 0; i < _decor.size(); i++) {
        if (!_ramasses[i]) {
            _decor[i].dessiner();
        }
    }
}

// V�rifi� si le personnage peut avancer
bool Niveau::caseEtLibre(int posX, int posY) {
    bool caselibre = true;
    int indice = indiceObjet(posX, posY, "solide");
    if (indice != -1) {
        caselibre = false;
    }
    return caselibre;
}

// Calcul le nombre de bonus pr�sent dans le niveau
int Niveau::nbBonus() {
    int bonus=0;
    for (int i=0; i<_decor.size(); i++) {
        if (_decor.at(i).getProp() == "bonus") {
            bonus++;
        }
    }
    return bonus;
}

// Tester si un bonus est pr�sent sur la case courante et si oui le r�cup�r�
void Niveau::testerBonusEtPrendre(int posX, int posY) {
    int indice = indiceObjet(posX, posY, "bonus");
    if (indice != -1 && !_ramasses[indice]) {
        _bonus--;
        _ramasses[indice] = true;
        _decor[indice].ramasser();
    }
}

// V�rifie si le joueur a gagn�
bool Niveau::gagne() {
    bool gagner = false;
    if (_bonus == 0 && _niveauCurent == 4) {
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

int Niveau::getBonus() {
    return _bonus;
}

void Niveau::setNiveau(const string& nomf, Dictionnaire& dico) {
    ifstream entree(nomf);
    if (!entree.is_open()) {
        throw string("Le fichier niveau n'est pas ouvert : ") + nomf;
    }

    int nbInt;
    entree >> nbInt;

    _decor.clear();  // optionnel : si tu veux vider l�ancien niveau

    for (int i = 0; i < nbInt && !entree.eof(); i++) {
        string nom;
        int x, y;
        entree >> nom >> x >> y;
        Objet o(_image, nom, dico, x * 16, y * 16);
        _decor.push_back(o);
    }

    entree.close();

    _ramasses.clear();
    _ramasses.resize(_decor.size(), false);

    _bonus = nbBonus();
    _nomFichier = nomf;
    setNiveauCurrent(nomf);
}

int Niveau::getNiveauCurent() {
    return _niveauCurent;
}

void Niveau::setNiveauCurrent(const std::string& nomf) {
    std::regex regex_num("niveau([0-9]+)\\.txt");
    std::smatch match;
    if (std::regex_search(nomf, match, regex_num)) {
        _niveauCurent = std::stoi(match[1]);
    }
}

void Niveau::chargerNiveau(int numero, Dictionnaire& dico) {
    // Construire le chemin du fichier : "./assets/niveauX.txt"
    std::string nomf = "./assets/niveau" + std::to_string(numero) + ".txt";

    // Appeler setNiveau avec le fichier et le dictionnaire
    setNiveau(nomf, dico);

    // Mettre � jour le num�ro de niveau courant
    _niveauCurent = numero;
}
