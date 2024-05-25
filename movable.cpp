#include "movable.h"
#include <QDebug>

Movable::Movable(int x, int y, Background* parent):DrawableElem(x, y, parent)
{
    this->parent = parent;
}

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
        pos_x = x;
        pos_y = y;
        parent->update(old_zone);
    }
}


