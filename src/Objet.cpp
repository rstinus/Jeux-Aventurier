#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Dictionnaire.h"
#include <vector>
#include <iostream>
#include "Tuile.h"
#include "Objet.h"
using namespace std;

// Constructeur
Objet::Objet (Image& image, string nom, Dictionnaire& dico, int posX, int posY) {
    _posX = posX;
    _posY = posY;
    Tuile temp;
    dico.recherche(nom, temp);
    _image = image;
    _ObjetX = temp.getX();
    _ObjetY = temp.getY();
    _prop = temp.getProp();
    _image.selectionnerRectangle(_ObjetX*16, _ObjetY*16, 16, 16);
}

// Dessiner une image
void Objet::dessiner() {
    _image.dessiner(_posX, _posY);
}

// R�cup�r� la propri�t�
string Objet::getProp() const {
    return _prop;
}

// R�cup�r� les coordonn�es x
int Objet::getX() const {
    return _posX;
}

// R�cup�r� les coordonn�es y
int Objet::getY() const {
    return _posY;
}

// Cacher un objet
void Objet::cache() {
    _prop = "cache";
}
