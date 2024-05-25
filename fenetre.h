#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include "background.h"
#include "personnage.h"
/// Objet correspondant à la fenêtre principale
class Fenetre : public QMainWindow
{
    Q_OBJECT

private:
    /// Widget central de la fenêtre
    Background* background;
    /// Widget d'exemple représentant un personnage
    Personnage* personnage;
public:
    explicit Fenetre(QWidget *parent = nullptr);

signals:

};

#endif // FENETRE_H
