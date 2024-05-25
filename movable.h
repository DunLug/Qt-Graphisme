#ifndef MOVABLE_H
#define MOVABLE_H

#include "drawableelem.h"

/// Classe utilisée pour pouvoir repositionner des éléments graphiques dans la fenêtre
/// Elle sert de classe de base pour RegularMove et Interactive, qui permettent de déplacer des éléments soit de manière régulière soit par interaction avec le joueur
class Movable : public DrawableElem
{
    Q_OBJECT
public:
    Movable(int x, int y, Background *parent);

    void positionner(int x, int y);
    /// Donne la position x courante de l'élément
    /// \return La position x de l'élément
    int get_pos_x() const {return pos_x;}
    /// Donne la position y courante de l'élément
    /// \return La position y de l'élément
    int get_pos_y() const {return pos_y;}



protected:
    /// Le widget de fond de fenêtre utilisé pour repositionner l'élément
    Background* parent;
};

#endif // MOVABLE_H
