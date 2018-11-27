#ifndef CIRCLE_H
#define CIRCLE_H
#include"shape.h"

class Circle:public Shape
{
public:
    Circle();
    void paint(QPainter &painter);
    void rotate(Shape *s, int d);
};

#endif // CIRCLE_H
