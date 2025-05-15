#ifndef TUILE_H_INCLUDED
#define TUILE_H_INCLUDED
#include "Image.h"
#include <string>
#include "Moteur.h"
#include <vector>
using namespace std;

class Tuile {
    string _nom;
    int _x;
    int _y;
    string _propriete;
public:

    Tuile();
    Tuile(string nom, int x, int y, string propriete);

    void afficher() const;

    string getNom() const;
    string getProp() const;
    int getX () const;
    int getY () const;
};


#endif // TUILE_H_INCLUDED
