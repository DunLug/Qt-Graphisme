#ifndef REGULARMOVE_H
#define REGULARMOVE_H

//#define ANIMATION
#ifdef ANIMATION
#include <QState>
#include <QPropertyAnimation>
#endif

#include "movable.h"
#include <QTimer>

/// Classe utilisée pour déplacer régulièrement des éléments graphiques, comme un ennemi
/// Il repose sur l'appel à intervalles réguliers de update_pos() qui doit être redéfini dans les classes filles pour obtenir le comportement souhaité
/// Cette classe permet également de mettre en œuvre des animations de personnages, si QStateMachine est installée et que la macro ANIMATION est définie 
class RegularMove : public Movable
{
    Q_OBJECT
#ifdef ANIMATION
    /// Le numéro de la frame de l'animation
    Q_PROPERTY(int frame READ frame WRITE setFrame)
    /// Le format des noms de fichiers utilisés pour animer le personnage
    Q_PROPERTY(QString basename READ _basename WRITE _setBasename);
#endif

public:
    RegularMove(int x, int y, Background *parent);
    /// Méthode appelée à intervalle régulier pour mettre à jour la position du personnage. Elle doit calculer la nouvelle position et la mettre à jour avec la méthode positionner(int x, int y)
    virtual void update_pos()=0;

#ifdef ANIMATION
    std::string direction() const;
    void set_direction(std::string);

    void init_animation_perso();
    void init_animation_ennemi(std::string);
    void positionner(int x, int y);
    void show_collision() {emit collision();}
#endif

private:
#ifdef ANIMATION
    void init_animation(std::string nom, int nb_frames);

    QString _basename() const;
    void _setBasename(QString basename);

    int frame();
    void setFrame(int frame);

    /// L'état dans lequel le personnage est dirigé vers la droite, utilisé pour avoir une animation spécifique à cet état
    QState* st_dr;
    /// L'état dans lequel le personnage est dirigé vers la gauche, utilisé pour avoir une animation spécifique à cet état
    QState* st_ga;
    /// L'état dans lequel le personnage est dirigé vers le haut, utilisé pour avoir une animation spécifique à cet état
    QState* st_ha;
    /// L'état dans lequel le personnage est dirigé vers le bas, utilisé pour avoir une animation spécifique à cet état
    QState* st_ba;
#endif
    /// Le timer utilisé pour appeler régulièrement update_pos()
    QTimer* timer;

private slots:
    void _update_pos();

#ifdef ANIMATION
signals:
    /// Le signal émis lors du changement de direction du personnage vers la gauche
    void left();
    /// Le signal émis lors du changement de direction du personnage vers la droite
    void right();
    /// Le signal émis lors du changement de direction du personnage vers le haut
    void up();
    /// Le signal émis lors du changement de direction du personnage vers le bas
    void down();
    /// Le signal émis lors d'une collision du personnage avec un ennemi
    void collision();

protected:
    /// Le numéro de la frame courante
    int m_frame;
    /// Le modèle de nom de fichier utilisé pour les animations
    QString m_basename;
    /// La machine d'états utilisée pour gérer les différentes animations
    QStateMachine* machine;
    /// La direction courante du personnage
    std::string dir;
    /// L'objet utilisé pour animer le personnage (modifier les images affichées)
    QPropertyAnimation animation;
    /// L'objet utilisé pour fluidifier le déplacement du personnage
    QPropertyAnimation mov_animation;
    /// L'état initial du personnage
    QState* first_state;

    void add_animation(int, int, int, int, std::string);
    void add_animation(QState*, int, int, int, int, std::string);
    void start_animation(QState* initial=nullptr);
#endif
};

#endif // REGULARMOVE_H
