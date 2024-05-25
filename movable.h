#ifndef MOVABLE_H
#define MOVABLE_H

#include "drawableelem.h"

class Movable : public DrawableElem
{
    Q_OBJECT
public:
    Movable(int x, int y, Background *parent);

    void positionner(int x, int y);
    int get_pos_x() const {return pos_x;}
    int get_pos_y() const {return pos_y;}



protected:
    Background* parent;
};

#endif // MOVABLE_H
