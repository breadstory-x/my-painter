#ifndef ELLIPSE_H
#define ELLIPSE_H
#include"shape.h"

class Ellipse:public Shape
{
public:
    Ellipse();
    void paint(QPainter &painter);
    void rotate_paint(QPainter &painter);
};

#endif // ELLIPSE_H
