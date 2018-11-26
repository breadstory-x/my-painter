#ifndef LINE_H
#define LINE_H
#include"shape.h"

class Line:public Shape
{
public:
    Line();
    void paint(QPainter &painter);
    void rotate_paint(QPainter &painter, int d);
};

#endif // LINE_H
