#include "drawableelem.h"
#include <QDebug>

/// Crée un élément dessinable et positionnable
/// \param x la position x de l'élément
/// \param y la position y de l'élément
/// \param parent le fond dans lequel dessiner l'élément. Le nouvel élément est abonné au parent pour recevoir les informations de redimensionnement
DrawableElem::DrawableElem(int x, int y, Background* parent) : Drawable(parent), pos_x(x), pos_y(y)
{
    parent->subscribe(this);
}

/// \brief Fonction appelée automatiquement lors du redimensionnement de la fenêtre
/// Cette fonction met à jour la position et la taille de l'élément en fonction de la nouvelle taille de la fenêtre
/// Elle ajoute également des marges si besoin afin de ne pas étirer l'image lors du redimensionnement
/// \param fx le facteur de redimensionnement fx
/// \param fy le facteur de redimensionnement fy
void DrawableElem::resized(double fx, double fy)
{
    QRect geom;
    // redimensionnement sans marge
    geom.setTop(pos_y*fy);
    geom.setLeft(pos_x*fx);
    geom.setWidth(sizeHint().width()*fx);
    geom.setHeight(sizeHint().height()*fy);

    correct_margins(geom);
    this->setGeometry(geom);
}

/// \brief Corrige les marges de l'élément lors d'un redimensionnement pour éviter toute déformation
/// Cette fonction a été implémentée lors de l'utilisation de la librairie pour coder un jeu Pacman, dans ce contexte, le plateau est défini par une grille de carrés qui peuvent être étirés lors du redimensionnement de la fenêtre. Afin d'éviter toute déformation des images dans ce cas, les marges sont corrigées pour que les éléments soient toujours de forme carrée et centrée dans la case correspondante.
/// \param geom La zone de dessin de l'élément, à modifier pour respecter le ratio de l'image
void DrawableElem::correct_margins(QRect& geom)
{
    // ajout de marges pour respecter l'aspect ratio
    if (geom.width() > geom.height())
    {
        geom.setLeft(geom.left()+(geom.width()-geom.height())/2);
        geom.setWidth(geom.height());
    }
    else if (geom.height() > geom.width())
    {
        geom.setTop(geom.top()+(geom.height()-geom.width())/2);
        geom.setHeight(geom.width());
    }
}
