#ifndef FENETRE_H
#define FENETRE_H

#include <QMainWindow>
#include "background.h"
#include "personnage.h"
class Fenetre : public QMainWindow
{
    Q_OBJECT

private:
    Background* background;
    Personnage* personnage;
public:
    explicit Fenetre(QWidget *parent = nullptr);

signals:

};

#endif // FENETRE_H
