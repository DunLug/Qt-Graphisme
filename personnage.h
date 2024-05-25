#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "interactive.h"

class Personnage : public Interactive
{
public:
    Personnage(int x, int y, Background *parent);
    void arrow_pressed(std::string);
    void key_pressed(char){}
};

#endif // PERSONNAGE_H
