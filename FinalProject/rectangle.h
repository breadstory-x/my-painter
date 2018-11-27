#ifndef RECTANGLE_H
#define RECTANGLE_H
#include<QPoint>
#include"shape.h"

class Rectangle : public Shape
{
public:
    Rectangle();
    void paint(QPainter &painter);
    void rotate(Shape *s, int d);
};

#endif // RECTANGLE_H
