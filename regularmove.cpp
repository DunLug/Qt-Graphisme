#include "regularmove.h"

#ifdef ANIMATION
#include <QtStateMachine/QStateMachine>
#include <QWidget>
#include <QPropertyAnimation>
#include <QDebug>
#endif

/// \brief Construit un élément graphique capable de se déplacer régulièrement
/// \param x la position x de départ de l'élément
/// \param y la position y de départ de l'élément
/// \param parent le fond de fenêtre dans lequel dessiner l'élément
/// Si la macro ANIMATION est définie, le déplacement d'un RegularMove se fait de manière fluide, sinon, l'image est redessinée directement à la nouvelle position.
RegularMove::RegularMove(int x, int y, Background* parent) : Movable(x, y, parent)
{
#ifdef ANIMATION
    machine = new QStateMachine(this);
    first_state = nullptr;
#endif
    timer = new QTimer(this);
    timer->setInterval(500);
    timer->setSingleShot(false);
    connect(timer, SIGNAL(timeout()), this, SLOT(_update_pos()));
    timer->start();
}

/// Slot utilisé pour mettre à jour la position de manière régulière. Elle appelle la fonction abstraite update_pos qui doit être redéfinie pour calculer la nouvelle position et appeler la méthode positionner.
/// \see Movable::positionner(int, int)
/// \see RegularMove::positionner(int, int)
void RegularMove::_update_pos()
{
    update_pos();
}

#ifdef ANIMATION
/// Redéfinition de la méthode Movable::positionner(int, int), qui permet de mettre à jour la position de manière fluide et animée.
/// Cette redéfinition n'est présente que dans le cas où la macro ANIMATION est définie, et nécessite l'installation de la librairie QStateMachine
/// Dans le cas contraire, l'appel à positionner(int, int) est redirigée vers Movable::positionner(int, int)
/// \see Movable::positionner(int, int)
void RegularMove::positionner(int x, int y)
{
    if (parent)
    {
        double factor_x = (double)parent->width()/(double)parent->base_width();
        double factor_y = (double)parent->height()/(double)parent->base_height();
        QPoint offset = QPoint(x*sizeHint().width()*factor_x, y*sizeHint().height()*factor_y);

        QRect geom;
        geom.setTop(y*sizeHint().height()*factor_y);
        geom.setLeft(x*sizeHint().width()*factor_x);
        geom.setWidth(sizeHint().width()*factor_x);
        geom.setHeight(sizeHint().height()*factor_y);
        correct_margins(geom);
        pos_x = x;
        pos_y = y;
        mov_animation.setTargetObject(this);
        mov_animation.setPropertyName("geometry");
        mov_animation.setStartValue(this->geometry());
        mov_animation.setEndValue(geom);
        mov_animation.setDuration(300);
        mov_animation.start();
        qDebug() << pos_x << pos_y << this->geometry()  << geom;
    }
}

/// Ajoute une animation pour le déplacement
/// \param start le numéro de la première frame de l'animation
/// \param end le numéro de la dernière frame de l'animation
/// \param loop le nombre de boucles d'animation à effectuer (-1 pour une animation infinie)
/// \param duration la durée d'une boucle
/// \param pattern le format du nom de fichier à utiliser pour rechercher les images de l'animation, le numéro de frame est indiqué par le placeholder %1
void RegularMove::add_animation(int start, int end, int loop, int duration, std::string pattern)
{
    add_animation(new QState(machine), start, end, loop, duration, pattern);
}

/// \brief Ajoute une animation pour le déplacement
/// Ajoute une animation pour le déplacement en fournissant explicitement le QState associé. Cela permet notamment de connecter le lancement du QState à la réception d'un signal, comme up(), down(), left() ou right()
/// \param state L'état dans lequel la machine d'état doit se trouver pour produire l'animation
/// \param start le numéro de la première frame de l'animation
/// \param end le numéro de la dernière frame de l'animation
/// \param loop le nombre de boucles d'animation à effectuer (-1 pour une animation infinie)
/// \param duration la durée d'une boucle
/// \param pattern le format du nom de fichier à utiliser pour rechercher les images de l'animation, le numéro de frame est indiqué par le placeholder %1
/// \see RegularMove::init_animation(std::string nom, int nb_frames)
void RegularMove::add_animation(QState* state, int start, int end, int loop, int duration, std::string pattern)
{
    if (!first_state)
    {
        first_state = state;
    }
    connect(state, SIGNAL(entered()), &animation, SLOT(stop()));
    connect(state, SIGNAL(entered()), &animation, SLOT(start()));
    state->assignProperty(&animation, "startValue", start);
    state->assignProperty(&animation, "endValue", end+1);
    state->assignProperty(&animation, "loopCount", loop);
    state->assignProperty(&animation, "duration", duration);
    state->assignProperty(this, "basename", QString::fromStdString(pattern));
}

/// Lance l'affichage d'une animation
/// \param initial L'état à utiliser pour l'animation. Si la valeur est à nullptr, la première animation créée est utilisée
void RegularMove::start_animation(QState *initial)
{
    if (!initial)
    {
        initial = first_state;
    }
    animation.setPropertyName("frame");
    animation.setTargetObject(this);

    machine->setInitialState(initial);
    machine->start();

    animation.start();
}

/// Donne le numéro de la frame courante
/// \return le numéro de la frame
int RegularMove::frame()
{
    return m_frame;
}

/// Modifie le numéro de la frame courante et modifie l'image en conséquence
/// \param frame Le numéro de la frame à utiliser
void RegularMove::setFrame(int frame)
{
    m_frame = frame;
    set_background_image(m_basename.arg(m_frame).toStdString());
}

/// Donne le format des noms de fichiers à utiliser pour l'animation
/// \return Le format des noms de fichiers à utiliser pour l'animation
QString RegularMove::_basename() const
{
    return m_basename;
}

/// Modifie le format des noms de fichiers à utiliser pour l'animation
/// \param basename Le format des noms de fichiers à utiliser pour l'animation
void RegularMove::_setBasename(QString basename)
{
    this->m_basename = basename;
}

/// Donne la direction courante du widget
/// \return La direction courante du widget parmi les possibilités "UP", "DOWN", "RIGHT", "LEFT"
std::string RegularMove::direction() const
{
    return dir;
}

/// Modifie la direction du widget et transmets des signaux pour adapter les animations en conséquence
/// \param direction La direction du widget parmi les possibilités "UP", "DOWN", "RIGHT", "LEFT"
void RegularMove::set_direction(std::string direction)
{
    if (direction == "UP")
    {
        emit up();
    }
    else if (direction == "DOWN")
    {
        emit down();
    }
    else if (direction == "RIGHT")
    {
        emit right();
    }
    else if(direction == "LEFT")
    {
        emit left();
    }
    dir = direction;
}

/// Méthode initialisant les différentes animations possibles du personnage PacMan
/// Crée quatre états (st_dr, st_ga, st_ba, st_ha) correspondants aux animations de Pacman pour ouvrir et fermer la bouche dans différentes directions
/// Ajoute également une animation supplémentaire, st_go, qui est obtenue à la réception d'un signal collision() dans n'importe quel état de départ de Pacman, et qui l'affiche tournant sur lui-même
void RegularMove::init_animation_perso()
{
    init_animation("pacman", 4);
    QState* st_go = new QState(machine);
    st_dr->addTransition(this, SIGNAL(collision()), st_go);
    st_ga->addTransition(this, SIGNAL(collision()), st_go);
    st_ba->addTransition(this, SIGNAL(collision()), st_go);
    st_ha->addTransition(this, SIGNAL(collision()), st_go);
    add_animation(st_go, 1, 4, 3, 500, "pacman_go_%1.png");
}

/// Méthode initialisant les différentes animations possibles des fantômes Pacman
/// Crée quatre états (st_dr, st_ga, st_ba, st_ha) correspondant aux animations des fantomes lorsqu'ils se déplacent dans l'une des quatre directions
/// \param nom Le nom du fantôme utilisé, parmi pinky, blinky, clyde et inky
void RegularMove::init_animation_ennemi(std::string nom)
{
    init_animation(nom, 2);
}

/// Méthode permettant d'initialiser les animations d'un RegularMove dans quatre directions possibles
/// Le format des noms de fichiers doit être de la forme {nom}_{dir}_{frame}.png, avec dir = {dr, ga, ba, ha}.
/// \param nom Le nom du personnage à animer (utilisé dans le nom de fichier)
/// \param nb_frames Le nombre de frames à utiliser (les fichiers ayant des frames allant de 1 à nb_frames, sans remplissage par des zéros
void RegularMove::init_animation(std::string nom, int nb_frames)
{
    st_dr = new QState(machine);
    st_ga = new QState(machine);
    st_ha = new QState(machine);
    st_ba = new QState(machine);

    st_dr->addTransition(this, SIGNAL(left()), st_ga);
    st_dr->addTransition(this, SIGNAL(up()), st_ha);
    st_dr->addTransition(this, SIGNAL(down()), st_ba);

    st_ga->addTransition(this, SIGNAL(up()), st_ha);
    st_ga->addTransition(this, SIGNAL(down()), st_ba);
    st_ga->addTransition(this, SIGNAL(right()), st_dr);

    st_ha->addTransition(this, SIGNAL(left()), st_ga);
    st_ha->addTransition(this, SIGNAL(down()), st_ba);
    st_ha->addTransition(this, SIGNAL(right()), st_dr);

    st_ba->addTransition(this, SIGNAL(left()), st_ga);
    st_ba->addTransition(this, SIGNAL(up()), st_ha);
    st_ba->addTransition(this, SIGNAL(right()), st_dr);

    int duration = 500;
    add_animation(st_dr, 1, nb_frames, -1, duration, nom + "_dr_%1.png");
    add_animation(st_ga, 1, nb_frames,  -1, duration, nom + "_ga_%1.png");
    add_animation(st_ha, 1, nb_frames, -1, duration, nom + "_ha_%1.png");
    add_animation(st_ba, 1, nb_frames,  -1, duration, nom + "_ba_%1.png");
    start_animation(st_dr);
}
#endif
