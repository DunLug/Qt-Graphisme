#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <QWidget>

/// Classe de base des éléments graphiques
/// Cette classe est utilisée pour afficher une couleur ou une image pour tous les éléments graphiques. Elle est principalement utilisée par Background et les classes dérivant de celle-ci
/// Pour pouvoir gérer des fonctionnalités plus avancées, comme le positionnement ou le déplacement, il est conseillé d'utiliser les classes dérivées
class Drawable : public QWidget
{
    Q_OBJECT
public:
    Drawable(QWidget *parent);
    void set_background_image(std::string filename);
    void set_background_color(int r, int g, int b, int a=255);
    void remove_inheritance();

};

#endif // DRAWABLE_H
