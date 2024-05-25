#include "movable.h"
#include <QDebug>

/// Crée un élément qui peut se déplacer dans l'écran
/// \param x la position x initiale de l'élément
/// \param y la position y initiale de l'élément
/// \param parent Le fond de fenêtre dans lequel dessiner l'élément. Celui-ci avertit le widget lors d'un redimensionnement de la fenêtre
Movable::Movable(int x, int y, Background* parent):DrawableElem(x, y, parent)
{
    this->parent = parent;
}

/// Déplace l'élément à une nouvelle position
/// \param x La nouvelle position x
/// \param y La nouvelle position y
void Movable::positionner(int x, int y)
{
    if (parent)
    {
        double factor_x = (double)parent->width()/(double)parent->base_width();
        double factor_y = (double)parent->height()/(double)parent->base_height();
        QPoint offset = QPoint(x*factor_x, y*factor_y);
        QRect old_zone = this->frameGeometry();
        old_zone = old_zone.marginsAdded(QMargins(5, 5, 5, 5));
        QRect geom;
        geom.setTop(y*factor_y);
        geom.setLeft(x*factor_x);
        geom.setWidth(sizeHint().width()*factor_x);
        geom.setHeight(sizeHint().height()*factor_y);
        correct_margins(geom);
        this->move(geom.topLeft());
        qDebug() << "Old_zone = " << old_zone << ", geom = " << geom;
        pos_x = x;
        pos_y = y;
        parent->update(old_zone);
    }
}


