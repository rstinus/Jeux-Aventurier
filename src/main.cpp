#include <vector>
#include "Dictionnaire.h"
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Objet.h"
#include "Niveau.h"

using namespace std;

int main(int, char**) // Version special du main, ne pas modifier
{
  // Initialisation du jeu
  Moteur moteur("Mon super jeu vidéo");

  // TODO: charger images, creer personnages, etc.
    Image image;
    Image coffref;
    Image coffreo;
    Image skin;
    Image GameOver;
    Image objet;
    Image Bravo;
    try {
        image = Image(moteur, "./assets/fond.png");
        coffref = Image(moteur, "./assets/coffre_ferme.png");
        coffreo = Image(moteur, "./assets/coffre_ouvert.png");
        skin = Image(moteur, "./assets/personnages.png");
        GameOver = Image(moteur, "./assets/gameover.png");
        objet = Image(moteur, "./assets/objets.png");
        Bravo = Image(moteur, "./assets/bravo.png");
    }
    // (... et le catch pour traiter l'exception)
    catch (runtime_error n) {
        cerr << n.what();
    }
    int skin_x = 1;
    int skin_y = 0;
    int ennemi1skin_x = 7;
    int ennemi1skin_y = 4;
    int ennemi2skin_x = 4;
    int ennemi2skin_y = 4;
    Personnage Guerrier(skin,32,16,skin_x*16,skin_y*16,'H');
    Personnage ennemi1(skin,5*16,16,ennemi1skin_x*16,ennemi1skin_y*16,'B');
    Personnage ennemi2(skin,16,5*16,ennemi2skin_x*16,ennemi2skin_y*16,'D');
    Dictionnaire dico();
    Niveau Niveau1(objet, "./assets/niveau1.txt", dico);

    bool quitter = false;

  // Boucle de jeu, appelee a chaque fois que l'ecran doit etre mis a jour
  // (en general, 60 fois par seconde)
  while (!quitter)
  {

    // I. Gestion des evenements
    Evenement evenement = moteur.evenementRecu();
    while (evenement != AUCUN)
    {
      switch (evenement)
      {
        // QUITTER = croix de la fenetre ou Echap
        case QUITTER_APPUYE:
          quitter = true;
          break;
        // TODO: gerer les autres evenements
        /*case ESPACE_APPUYE:
            etatcoffre = !etatcoffre;
            break;*/
        case GAUCHE_APPUYE:
            Niveau1.testerBonusEtPrendre(Guerrier.getPosx(), Guerrier.getPosy());
            Guerrier.mettreJourDirection('G');
            Guerrier.allerGauche(Niveau1);
            break;
        case DROITE_APPUYE:
            Niveau1.testerBonusEtPrendre(Guerrier.getPosx(), Guerrier.getPosy());
            Guerrier.mettreJourDirection('D');
            Guerrier.allerDroite(Niveau1);
            break;
        case HAUT_APPUYE:
            Niveau1.testerBonusEtPrendre(Guerrier.getPosx(), Guerrier.getPosy());
            Guerrier.mettreJourDirection('B');
            Guerrier.allerHaut(Niveau1);
            break;
        case BAS_APPUYE:
            Niveau1.testerBonusEtPrendre(Guerrier.getPosx(), Guerrier.getPosy());
            Guerrier.mettreJourDirection('H');
            Guerrier.allerBas(Niveau1);
            break;
        case ESPACE_APPUYE:
            quitter = true;
        default:
          break;
        }



      evenement = moteur.evenementRecu();
    }


    // II. Mise à jour de l'état du jeu

    // TODO: faire bouger vos personnages, etc.
    if (moteur.animationsAmettreAjour() == true) {
        ennemi1.avancer(Niveau1);
        ennemi2.avancer(Niveau1);
        Guerrier.mettreAjourAnimation();
    }


    // III. Generation de l'image à afficher

    moteur.initialiserRendu(); // efface ce qui avait ete affiche precedemment et reinitalise en ecran noir

    // TODO: afficher vos personnages, objets, etc.
    Niveau1.dessiner();
    /*if (etatcoffre == false){
        coffref.dessiner(posx,posy);
    }
    else {
        coffreo.dessiner(posx,posy);
    }*/
    Guerrier.dessine();
    ennemi1.dessine();
    ennemi2.dessine();
    if (Guerrier.touche(ennemi1) || Guerrier.touche(ennemi2)) {
        int posxGO = LARGEUR_FENETRE/2-49.5;
        int posyGO = HAUTEUR_FENETRE/2-12;
        GameOver.dessiner(posxGO, posyGO);
        quitter = true;
    }
    if (Niveau1.gagne() == true) {
        //int posxB = LARGEUR_FENETRE/2-49.5;
        //int posyB = HAUTEUR_FENETRE/2-12;
        int posxB = LARGEUR_FENETRE/2-49.5;
        int posyB = HAUTEUR_FENETRE/2-12;
        Bravo.dessiner(posxB, posyB);
        quitter = true;
    }
    /*
      Affiche l'image en se cadencant sur la frequence de
      rafraichissement de l'ecran (donc va en general mettre le
      programme en pause jusqu'a ce que l'ecran soit rafraichi). En
      general, 60 images fois par seconde, mais ca peut dependre du
      materiel
    */
    moteur.finaliserRendu();
  }
  if (quitter == true) {
    moteur.attendre(2);
  }

  return 0;
}
