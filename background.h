#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "drawable.h"
#include <QPaintEvent>
#include <QDebug>

/// Classe utilisée dans Fenetre comme widget central, celui-ci permet d'afficher une image de fond et de gérer le redimensionnement de la fenêtre en avertissant les widgets enfants
class Background : public Drawable
{
    Q_OBJECT
public:
    explicit Background(QWidget* parent);

    void subscribe(Drawable* child);

    int base_width() const;
    int base_height() const;

    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent *event){qDebug() << event->rect();};

private:
    /// La taille de base du Background
    const QSize base_size = QSize(1280, 600);

signals:
    /// Signal émis en cas de redimensionnement de la fenêtre. Celui indique des facteurs de redimensionnement utilisés par les widgets
    void resized(double, double);
};

#endif // BACKGROUND_H
