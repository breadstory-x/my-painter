#ifndef VRECT_H
#define VRECT_H
#include"shape.h"


class Vrect:public Shape
{
public:
    Vrect();
    void paint(QPainter &painter);
    void rotate_paint(QPainter &painter);
};

#endif // VRECT_H
