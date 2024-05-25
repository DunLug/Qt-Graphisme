#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "movable.h"
#include <QKeyEvent>
#include <string>
#include <QTimer>
class Interactive : public Movable
{
    Q_OBJECT
private:
    char key;
    std::string arrow;
    bool is_key_pressed;
    bool is_arrow_pressed;
    QTimer timer;

public:
    Interactive(int x, int y, Background *parent);
    virtual void key_pressed(char key)=0;
    virtual void arrow_pressed(std::string cmd)=0;
    void set_repetition_delay(int delay_ms);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void _manage_timeout();
};

#endif // INTERACTIVE_H
