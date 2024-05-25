#include "interactive.h"


Interactive::Interactive(int x, int y, Background* parent):Movable(x, y, parent)
{
    setFocus();
    connect(&timer, SIGNAL(timeout()), this, SLOT(_manage_timeout()));
    set_repetition_delay(10);
    timer.setSingleShot(false);
}


void Interactive::set_repetition_delay(int delay_ms)
{
    timer.setInterval(delay_ms);
}

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
