#include <vector>
#include <iostream>
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Tuile.h"
#include "Dictionnaire.h"

using namespace std;

int main(int, char**)
{
    Dictionnaire d("./assets/dictionnaire.txt");
    d.afficher();
    cout << d.recherche("Fauteuil") << endl;
    return 0;
}
