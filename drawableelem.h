#ifndef DRAWABLEELEM_H
#define DRAWABLEELEM_H

#include "drawable.h"
#include "background.h"

/// Classe permettant de dessiner un élément à une position donnée
/// Initialement, cette classe sert à positionner les éléments sur une grille, elle a ensuite été modifiée pour permettre un déplacement plus fluide.
class DrawableElem : public Drawable
{
    Q_OBJECT
public:
    DrawableElem(int x, int y, Background* parent);

    /// Retourne une indication sur la taille théorique de l'élément, cette taille est susceptible de ne pas correspondre à la vraie taille du widget.
    QSize sizeHint() const {  return QSize(40, 40);}

public slots:
    void resized(double, double);


protected:
    void correct_margins(QRect& geom);
    /// Position x du widget
    int pos_x;
    /// Position y du widget
    int pos_y;
};

#endif // DRAWABLEELEM_H
