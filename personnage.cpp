#include "personnage.h"

Personnage::Personnage(int x, int y, Background* parent) : Interactive(x, y, parent)
{
    //init_animation_perso();
    set_background_color(255, 0, 0);
}

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
