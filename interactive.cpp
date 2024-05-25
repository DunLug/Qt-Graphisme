#include "interactive.h"


/// Construit un widget qui peut gérer des interactions clavier
/// \param x la position x initiale
/// \param y la position y initiale
/// \param parent Le fond de fenêtre dans lequel dessiner le widget
Interactive::Interactive(int x, int y, Background* parent):Movable(x, y, parent)
{
    setFocus();
    connect(&timer, SIGNAL(timeout()), this, SLOT(_manage_timeout()));
    set_repetition_delay(10);
    timer.setSingleShot(false);
}

/// Modifie le délai entre deux répétitions de touches, lorsque la touche reste enfoncée
/// \param delay_ms Le délai entre deux appels de key_pressed ou arrow_pressed, lorsque la touche reste enfoncée
void Interactive::set_repetition_delay(int delay_ms)
{
    timer.setInterval(delay_ms);
}

/// Méthode héritée de QWidget, qui est appelée lors de l'appui d'une touche par l'utilisateur
/// \param event Objet contenant les informations sur l'appui de la touche, notamment la touche actuellement utilisée
void Interactive::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        arrow = "UP";
        is_arrow_pressed = true;
        timer.start();
        break;
    case Qt::Key_Down:
        arrow = "DOWN";
        is_arrow_pressed = true;
        timer.start();
        break;
    case Qt::Key_Left:
        arrow = "LEFT";
        is_arrow_pressed = true;
        timer.start();
        break;
    case Qt::Key_Right:
        arrow = "RIGHT";
        is_arrow_pressed = true;
        timer.start();
        break;
    default:
        QString text = event->text();
        if (text.size() == 1)
        {
            QChar ch = text[0];
            if (ch.isLetterOrNumber())
            {
                key = ch.toLatin1();
                is_key_pressed = true;
                timer.start();
            }
        }
    }
}

/// Méthode héritée de QWidget, qui est appelée automatiquement lorsque la touche est relâchée
/// \param event Objet contenant les données sur l'événement, notamment la touche relâchée
void Interactive::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Up:
        if (arrow == "UP")
        {
            is_arrow_pressed=false;
            timer.stop();
        }
        break;
    case Qt::Key_Down:
        if (arrow == "DOWN")
        {
            is_arrow_pressed=false;
            timer.stop();
        }
        break;
    case Qt::Key_Left:
        if (arrow == "LEFT")
        {
            is_arrow_pressed=false;
            timer.stop();
        }
        break;
    case Qt::Key_Right:
        if (arrow == "RIGHT")
        {
            is_arrow_pressed=false;
            timer.stop();
        }
        break;
    default:
        QString text = event->text();
        if (text.size() == 1)
        {
            QChar ch = text[0];
            if (ch.isLetterOrNumber() && key == ch.toLatin1())
            {
                is_key_pressed = false;
                timer.stop();
            }
        }
    }
}


/// Gère la répétition des touches lorsque la touche reste enfoncée, en réappelant régulièrement les méthodes correspondantes
/// \see Interactive::arrow_pressed(char arrow)
/// \see Interactive::key_pressed(std::string key)
void Interactive::_manage_timeout()
{
    if (is_arrow_pressed)
    {
        arrow_pressed(arrow);
    }
    else if (is_key_pressed)
    {
        key_pressed(key);
    }
    else
    {
        timer.stop();
    }
}
