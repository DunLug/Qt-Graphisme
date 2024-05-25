#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "drawable.h"
#include <QPaintEvent>
#include <QDebug>
class Background : public Drawable
{
    Q_OBJECT
public:
    explicit Background(QWidget* parent);

    void subscribe(Drawable* child);

    int base_width() const;
    int base_height() const;

    void resizeEvent(QResizeEvent* event);
    void paintEvent(QPaintEvent *event){qDebug() << event->rect();};

private:
    const QSize base_size = QSize(1280, 600);

signals:
    void resized(double, double);
};

#endif // BACKGROUND_H
