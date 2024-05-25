#include "fenetre.h"
#include "personnage.h"

/// Construit la fenêtre et initialise un personnage pour la démonstration
/// \param parent Le parent de la fenêtre, ici nécéssairement nullptr
Fenetre::Fenetre(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Space Invaders");
    background = new Background(this);
    this->setCentralWidget(background);
    this->resize(800, 500);
    personnage = new Personnage(10, 10, background);
}
