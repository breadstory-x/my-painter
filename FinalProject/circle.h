#ifndef CIRCLE_H
#define CIRCLE_H
#include"shape.h"

class Circle:public Shape
{
public:
    Circle();
    void paint(QPixmap *pix);
};

#endif // CIRCLE_H
