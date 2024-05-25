#include "fenetre.h"
#include "personnage.h"

Fenetre::Fenetre(QWidget *parent)
    : QMainWindow{parent}
{
    this->setWindowTitle("Space Invaders");
    background = new Background(this);
    this->setCentralWidget(background);
    this->resize(800, 500);
    personnage = new Personnage(10, 10, background);
}
