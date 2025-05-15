#include "Image.h"
#include <string>
#include "Moteur.h"
#include "Tuile.h"
#include <vector>
using namespace std;

// Constructeur vide
Tuile::Tuile() {}

// Constructeur
Tuile::Tuile(string nom, int x, int y, string propriete) {
    _nom = nom;
    _x = x;
    _y = y;
    _propriete = propriete;
}

// Afficher une tuile
void Tuile::afficher() const {
    cout << _nom << " : x=" << _x << ", y=" << _y << ", " << _propriete << endl;
}

// Récupérer le nom d'une tuile
string Tuile::getNom() const {
    return _nom;
}

// Récupérer les coordonnées x d'une tuile
int Tuile::getX () const {
    return _x;
}

// Récupérer les coordonnées y d'une tuile
int Tuile::getY () const {
    return _y;
}

// Récupérer la propriété d'une tuile
string Tuile::getProp() const {
    return _propriete;
}
