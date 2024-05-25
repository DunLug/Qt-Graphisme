#ifndef ANIMATEDWIDGET_H
#define ANIMATEDWIDGET_H

#include <QtStateMachine/QStateMachine>
#include <QWidget>
#include <QPropertyAnimation>
#include "regularmove.h"

/// Classe utilisée pour afficher un élément animé
/// L'élément peut réaliser des animations continues (ex: fermeture de la bouche d'un Pacman), des animations ponctuelles (ex: infliction d'un coup)
/// Plusieurs animations peuvent être chargées et lancées selon le comportement voulu
/// La classe nécessite l'utilisation de la librairie QStateMachine, afin de modifier l'ensemble du code en conséquence, il faut également définir la macro ANIMATION dans le fichier .pro
class AnimatedWidget : public RegularMove
{
    Q_OBJECT
    /// Propriété utilisée pour gérer la frame courante
    Q_PROPERTY(int frame READ frame WRITE setFrame)
    /// Propriété utilisée pour gérer le format de nom de fichier d'image
    Q_PROPERTY(QString basename READ basename WRITE setBasename);
    /// Propriété utilisée pour gérer le nombre de caractères minimal à utiliser pour gérer le numéro de frame
    Q_PROPERTY(int fillwidth READ fillwidth WRITE setFillwidth);

public:
    explicit AnimatedWidget(int x, int y, Background *parent = nullptr);
    /// Récupère le numéro de la frame courante
    /// \return le numéro de la frame
    int frame();
    void setFrame(int frame);

    QString basename() const;
    void setBasename(QString basename);

    int fillwidth() const;
    void setFillwidth(int fillwidth);

    void add_animation(int, int, int, int, QString, int fillwidth=0);
    void add_animation(QState*, int, int, int, int, QString, int fillwidth=0);
    void start_animation(QState* initial=nullptr);

protected:
    /// Le numéro de la frame courante
    int m_frame;
    /// Le nombre de 0 à rajouter pour compléter le numéro de la frame
    int m_fillwidth;
    /// Le nom de l'image à utiliser, avec %1 représentant le numéro de la frame (remplacé par un nombre m_frame complété de 0 à gauche pour avoir une taille minimale m_fillwidth)
    QString m_basename;
    /// La machine d'états utilisée pour le choix de l'animation
    QStateMachine* machine;
    /// La classe utilisée pour mettre à jour régulièrement le numéro de frame et adapter l'image en conséquence
    QPropertyAnimation animation;
    /// La première animation à utiliser par défaut
    QState* first_state;
};

#endif // ANIMATEDWIDGET_H
