#include "background.h"
#include <QResizeEvent>

/// Construit un fond de fenêtre pour afficher une image et gérer l'ensemble des composants dessinés
/// \param parent Le parent du Background (ici la fenêtre principale)
/// \see Fenetre
Background::Background(QWidget *parent) : Drawable(parent)
{
    set_background_image("background.png");
}

/// Événement généré lors du redimensionnement de la fenêtre, pour indiquer aux widgets de mettre à jour leur taille
/// Ici, l'événement est capté par Background qui retransmets cet événement sous la forme d'un signal
/// \param event L'événement de redimensionnement (non utilisé)
void Background::resizeEvent(QResizeEvent* event)
{
    double fx, fy;
    fx = (double)this->width()/(double)base_size.width();
    fy = (double)this->height()/(double)base_size.height();
    emit resized(fx, fy);
}

/// Enregistre un widget pour qu'il puisse être averti en cas de redimensionement de la fenêtre
/// \param child Le widget à inscrire
void Background::subscribe(Drawable* child)
{
    connect(this, SIGNAL(resized(double, double)), child, SLOT(resized(double, double)));
}

/// Redonne la largeur de base du Background
/// La taille de base est une simple indication, qui sert de référence de départ. Elle n'a pas de valeur intrinsèque
/// \return La largeur de base du Background
int Background::base_width() const
{
    return base_size.width();
}

/// Redonne la hauteur de base du Background
/// La taille de base est une simple indication, qui sert de référence de départ. Elle n'a pas de valeur intrinsèque
/// \return La hauteur de base du Background
int Background::base_height() const
{
    return base_size.height();
}
