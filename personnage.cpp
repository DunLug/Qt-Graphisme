#include "personnage.h"

/// Construit un personnage en lui attribuant une apparence de carré rouge
/// \param x la position x initiale
/// \param y la position y initiale
/// \param parent Le fond de fenêtre dans lequel dessiner le Personnage
Personnage::Personnage(int x, int y, Background* parent) : Interactive(x, y, parent)
{
    //init_animation_perso();
    set_background_color(255, 0, 0);
}

/// Méthode redéfinisant Interactive::arrow_pressed(std::string) afin de gérer les interactions utilisateurs
/// \param dir La direction de la flèche appuyée
void Personnage::arrow_pressed(std::string dir)
{
    if (dir == "UP")
    {
        pos_y -= 10;
    }
    else if (dir  == "DOWN")
    {
        pos_y += 10;
    }
    else if (dir == "LEFT")
    {
        pos_x -= 10;
    }
    else if(dir == "RIGHT")
    {
        pos_x += 10;
    }

    positionner(pos_x, pos_y);
}
