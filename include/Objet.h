#ifndef OBJET_H_INCLUDED
#define OBJET_H_INCLUDED
#include "Image.h"
#include <string>
#include "Moteur.h"
#include <vector>
#include "Tuile.h"
#include <fstream>
using namespace std;

class Objet {
    string _prop;
    Image _image;
    int _posX;
    int _posY;
    int _ObjetX;
    int _ObjetY;
    bool _ramasse = false;

public :
    Objet (Image& image, string nom, Dictionnaire& dico, int posX, int posY);
    void dessiner();
    string getProp() const;
    int getX () const;
    int getY () const;
    void cache();
    bool estRamasse() const;
    void ramasser();
};


#endif // OBJET_H_INCLUDED
