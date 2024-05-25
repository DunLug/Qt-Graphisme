#include "drawable.h"
#include "consts.h"
#include "background.h"

/// Crée un widget dessinable à l'écran
/// \param parent le widget parent dans lequel dessiner le nouvel élément
Drawable::Drawable(QWidget *parent) :
    QWidget(parent)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
}

/// \brief Supprime l'héritage des styles
/// Les styles sont gérés par le biais d'une feuille de style CSS. Celle-ci transmets les modifications aux éléments enfant. Pour éviter ce problème, il est possible d'utiliser cette fonction pour remettre à zéro les styles.
void Drawable::remove_inheritance()
{
    this->setStyleSheet("border-image: none; background-color:none");
}

/// \brief Modifie l'image de fond du widget
/// \param filename Le nom de l'image. Celle-ci doit se trouver dans un dossier images/, lui-même présent dans le répertoire d'exécution (par défaut, le dossier commençant par build, dans lequel on trouve l'exécutable.
/// \see globals::IMG_PATH
void Drawable::set_background_image(std::string filename)
{
    QString stylesheet = "border-image: url(";
    stylesheet += QString::fromStdString(globals::IMG_PATH) + QString::fromStdString(filename) + ");";
    this->setStyleSheet(stylesheet);
    qDebug() << this->styleSheet();
}

/// \brief Modifie la couleur de fond du widget
/// Fonction simple pour développer les applications sans avoir à créer d'images
/// \param r la quantité de rouge (0-255)
/// \param g la quantité de vert (0-255)
/// \param b la quantité de bleu (0-255)
/// \param a la transparence (0-255)
void Drawable::set_background_color(int r, int g, int b, int a)
{
    QColor color(r, g, b, a);
    QString stylesheet = "border-image: none;"
                         "background-color: rgba(%1, %2, %3, %4);";
    stylesheet = stylesheet.arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    this->setStyleSheet(stylesheet);
}
