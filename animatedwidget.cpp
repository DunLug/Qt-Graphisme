#include "animatedwidget.h"

/// \brief Constructeur de la classe AnimatedWidget
/// Construit un widget qui peut être animé selon différents états
/// Créé initialement pour animer le personnage Pacman, pour qu'il ouvre et ferme la bouche régulièrement et dans toutes les directions possibles
/// Nécessite l'installation de QStateMachine
/// \param x la position x du widget
/// \param y la position y du widget
/// \param parent le widget central de la fenêtre, de type Background et créé dans la classe Fenetre
/// 
AnimatedWidget::AnimatedWidget(int x, int y, Background *parent) : RegularMove(x, y, parent)
{
    machine = new QStateMachine(this);
    first_state = nullptr;
}

/// \brief Charge une nouvelle animation
/// Crée une nouvelle animation. Si aucune animation n'est encore créée, il s'agit de l'animation initiale. Sinon elle est lancée par l'émission d'un signal
/// \param start le numéro de la première image
/// \param end le numéro de la dernière image
/// \param loop indique le nombre de répétitions de l'animation. Mettre 1 pour un seul tour, 4 pour quatre tours, 0 pour ne pas effectuer l'animation et -1 pour tourner en boucle
/// \param duration la durée d'une boucle d'animation
/// \param pattern le nom de fichier des images, en remplaçant %1 par le numéro de la frame courante
/// \param fillwidth indique la taille de remplissage du numéro de frame, s'il est égal à 2, le numéro de frame sera écrit 01, 02... 10. S'il est égal à 1, le numéro de frame sera écrit 1, 2...10.
///
void AnimatedWidget::add_animation(int start, int end, int loop, int duration, QString pattern, int fillwidth)
{
    add_animation(new QState(machine), start, end, loop, duration, pattern, fillwidth);
}

/// \brief Charge une nouvelle animation à partir d'un QState déjà créé
/// Méthode plus complète, permettant de créer des états manuellement et des les lier pour former une machine d'états plus avancée
/// Nécessite de créer manuellement les QState et des les manipuler
/// \see AnimatedWidget::add_animation(int start, int end, int loop, int duration, QString pattern, int fillwidth)
/// \see https://doc.qt.io/qt-6/qstate.html
void AnimatedWidget::add_animation(QState* state, int start, int end, int loop, int duration, QString pattern, int fillwidth)
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
    state->assignProperty(this, "basename", pattern);
    state->assignProperty(this, "fillwidth", fillwidth);
}

/// \brief Démarre une animation
/// \param initial L'animation à lancer, si elle est nulle, l'animation par défaut est utilisée
void AnimatedWidget::start_animation(QState *initial)
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

int AnimatedWidget::frame()
{
    return m_frame;
}

/// Modifie la valeur de la frame courante et met à jour l'image en conséquence
/// \param frame la nouvelle frame
void AnimatedWidget::setFrame(int frame)
{
    m_frame = frame;
    set_background_image(m_basename.arg(m_frame, m_fillwidth, 10, QChar('0')).toStdString());
}

/// Récupère le format de nom de fichier utilisé, avec %1 pour représenter le numéro de frame
/// \return le format de nom de fichier utilisé
QString AnimatedWidget::basename() const
{
    return m_basename;
}

/// Modifie le chemin des images
/// \param basename le chemin des images, par exemple "dir1/dir2/frame_%1.png"
void AnimatedWidget::setBasename(QString basename)
{
    this->m_basename = basename;
}

/// Récupère le nombre de caractères à utiliser pour le numéro de frame
/// \return Le nombre de caractères à utiliser pour le numéro de frame
int AnimatedWidget::fillwidth() const
{
    return m_fillwidth;
}

/// Modifie le nombre de caractères à utiliser pour le numéro de frame
/// Si le numéro de frame vaut 4, le placeholder %1 sera remplacé par un nombre éventuellement rempli de 0 pour avoir 4 caractères (0001, 0002...0101...)
/// \param fillwidth Le nombre de caractères à utiliser pour le numéro de frame
void AnimatedWidget::setFillwidth(int fillwidth)
{
    m_fillwidth = fillwidth;
}
