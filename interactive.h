#ifndef INTERACTIVE_H
#define INTERACTIVE_H

#include "movable.h"
#include <QKeyEvent>
#include <string>
#include <QTimer>
/// Classe permettant de récupérer les appuis de touche de l'utilisateur, afin de contrôler des widgets
class Interactive : public Movable
{
    Q_OBJECT
private:
    /// Touche actuellement appuyée
    char key;
    /// Flèche du clavier actuellement appuyée
    std::string arrow;
    /// Indique si une touche est actuellement appuyée
    bool is_key_pressed;
    /// Indique si une flèche est actuellement appuyée
    bool is_arrow_pressed;
    /// Timer utilisé pour gérer la répétition des touches dans le logiciel, cela permet d'empêcher l'utilisateur d'accélérer le déplacement du personnage en modifiant les paramètres au niveau du système d'exploitation
    QTimer timer;

public:
    Interactive(int x, int y, Background *parent);
    /// Méthode appelée lorsqu'une touche est appuyée, ou de manière régulière lorsque la touche reste enfoncée
    /// \param key La touche actuellement enfoncée
    virtual void key_pressed(char key)=0;
    /// Méthode appelée lorsqu'une flèche est appuyée, ou de manière régulière lorsque la flèche reste enfoncée
    /// \param cmd La flèche actuellement enfoncée, sous la forme "UP", "DOWN", "RIGHT", ou "LEFT"
    virtual void arrow_pressed(std::string cmd)=0;
    void set_repetition_delay(int delay_ms);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void _manage_timeout();
};

#endif // INTERACTIVE_H
