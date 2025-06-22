#include "Image.h"
#include "Personnage.h"
#include <string>
#include "Moteur.h"
using namespace std;

// Constructeur vide
Personnage::Personnage() {
    _PersPosx = 16;
    _PersPosy = 16;
    _direction = 4;
    _frame = 0;
}

// Constructeur
Personnage::Personnage(Image player, int PersPosx, int PersPosy, int skin_x, int skin_y, char direction) {
    _player = player;
    _PersPosx = PersPosx;
    _PersPosy = PersPosy;
    _skin_x = skin_x;
    _skin_y = skin_y;
    _direction = direction;
    _player.selectionnerRectangle(_skin_x,_skin_y,16,16);
    _animationX = skin_x;
    _animationY = skin_y;
}

Personnage::Personnage(Image player, int PersPosx, int PersPosy, int skin_x, int skin_y, char direction, Dictionnaire& dico) {
    _player = player;
    _PersPosx = PersPosx;
    _PersPosy = PersPosy;
    _skin_x = skin_x;
    _skin_y = skin_y;
    _direction = direction;
    _player.selectionnerRectangle(_skin_x,_skin_y,16,16);
    _animationX = skin_x;
    _animationY = skin_y;
    _dico = dico;
}

// Déssiné un personnage
void Personnage::dessine() {
    _player.dessiner(_PersPosx, _PersPosy);
}

// Vérifie si le personnage à atteint le bord du jeux
bool Personnage::bordatteint(){
    bool bordure = true;
    switch (_direction) {
        case 'H':
            if (_PersPosy < MAXY) {
                bordure = false;
            }
            break;
        case 'B':
            if (_PersPosy > MINXY) {
                bordure = false;
            }
            break;
        case 'D':
            if (_PersPosx < MAXX) {
                bordure = false;
            }
            break;
        case 'G':
            if (_PersPosx > MINXY) {
                bordure = false;
            }
            break;
    }
    return bordure;
}

// Faire aller à droite le personnage
void Personnage::allerDroite(Niveau& niveau){
    _PersPosx += 16;
    if ((niveau.caseEtLibre(_PersPosx, _PersPosy) == false)){
        _PersPosx -= 16;
    }
    std::cout<<_PersPosx << "   " << _PersPosy << endl;
    niveauSuivant(niveau);
}

// Faire aller à gauche le personnage
void Personnage::allerGauche(Niveau& niveau){
    _PersPosx -= 16;
    if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false){
        _PersPosx += 16;
    }
    std::cout<<_PersPosx << "   " << _PersPosy << endl;
    niveauSuivant(niveau);
}

// Faire aller en bas le personnage
void Personnage::allerBas(Niveau& niveau){
    _PersPosy += 16;
    if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false){
        _PersPosy -= 16;
    }
    std::cout<<_PersPosx << "   " << _PersPosy << endl;
    niveauSuivant(niveau);
}

// Faire aller en haut le personnage
void Personnage::allerHaut(Niveau& niveau){
    _PersPosy -= 16;
    if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false){
        _PersPosy += 16;
    }
    std::cout<<_PersPosx << "   " << _PersPosy << endl;
    niveauSuivant(niveau);
}

// Mettre à jour la direction
void Personnage::mettreJourDirection(char direction) {
    _direction = direction;
    switch (_direction) {
        case 'H':
            _animationX = _skin_x;
            _animationY = _skin_y;
            _player.selectionnerRectangle(_skin_x,_skin_y,16,16);
            break;
        case 'B':
            _animationX = _skin_x;
            _animationY = _skin_y+48;
            _player.selectionnerRectangle(_skin_x,_skin_y+48,16,16);
            break;
        case 'D':
            _animationX = _skin_x;
            _animationY = _skin_y+32;
            _player.selectionnerRectangle(_skin_x,_skin_y+32,16,16);
            break;
        case 'G':
            _animationX = _skin_x;
            _animationY = _skin_y+16;
            _player.selectionnerRectangle(_skin_x,_skin_y+16,16,16);
            break;
    }
}

// Faire avancer les ennemis
void Personnage::avancer(Niveau& niveau) {
    int mouvementEnnemi = rand() % 4;
    switch (mouvementEnnemi) {
        case 0:
            _direction = 'H';
            _PersPosy += 16;
            if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false) {
                _PersPosy -= 16;
            }
            else {
                _direction = 'B';
                mettreJourDirection(_direction);
            }
            break;
        case 1:
            _direction = 'B';
            _PersPosy -= 16;
            if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false) {
                _PersPosy += 16;
            }
            else {
                _direction = 'H';
                mettreJourDirection(_direction);
            }
            break;
        case 2:
            _direction = 'D';
            _PersPosx += 16;
            if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false) {
                _PersPosx -= 16;
            }
            else {
                _direction = 'G';
                mettreJourDirection(_direction);
            }
            break;
        case 3:
            _direction = 'G';
            _PersPosx -= 16;
            if (niveau.caseEtLibre(_PersPosx, _PersPosy) == false) {
                _PersPosx += 16;
            }
            else {
                _direction = 'D';
                mettreJourDirection(_direction);
            }
            break;
    }
}

// Récupéré les coordonnées x du personnage
int Personnage::getPosx() {
    return _PersPosx;
}

// Récupéré les coordonnées y du personnage
int Personnage::getPosy() {
    return _PersPosy;
}

// Vérifie si le joueur est touché par 1 ennemi
bool Personnage::touche(Personnage& J) {
    return (_PersPosx == J.getPosx() && _PersPosy == J.getPosy());
}

// Met à jour l'animation pour donner un effet de mouvement
void Personnage::mettreAjourAnimation() {
    if (_frame % 4 == 0) {
        _frame = 0;
    }
    switch (_frame) {
    case 0:
        _player.selectionnerRectangle(_skin_x-TAILLE_CASE, _animationY, TAILLE_CASE, TAILLE_CASE);
        break;
    case 1:
        _player.selectionnerRectangle(_skin_x, _animationY, TAILLE_CASE, TAILLE_CASE);
        break;
    case 2:
        _player.selectionnerRectangle(_skin_x+TAILLE_CASE, _animationY, TAILLE_CASE, TAILLE_CASE);
        break;
    case 3:
        _player.selectionnerRectangle(_skin_x, _animationY, TAILLE_CASE, TAILLE_CASE);
        break;
    }
    _frame++;
}

void Personnage::niveauSuivant(Niveau& niveau) {
    if (_PersPosx == 128 && _PersPosy == 16 && niveau.getBonus() == 0) {
        switch (niveau.getNiveauCurent()) {
        case 1:
            niveau.chargerNiveau(2, _dico);
            break;
        case 2:
            niveau.chargerNiveau(3, _dico);
            break;
        case 3:
            niveau.chargerNiveau(4, _dico);
            break;
        case 4:
            niveau.gagne();
            break;
        }
    }
}
