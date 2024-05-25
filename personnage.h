#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include "interactive.h"

/// Classe d'exemple représentant un Personnage, pour montrer l'utilisation de la classe Interactive
class Personnage : public Interactive
{
public:
    Personnage(int x, int y, Background *parent);
    void arrow_pressed(std::string);
    /// Redéfinition de la méthode abstraite Interactive::key_pressed(char), qui ne fait rien ici mais doit être redéfinie pour permettre l'instanciation de la classe Personnage
    void key_pressed(char){}
};

#endif // PERSONNAGE_H
