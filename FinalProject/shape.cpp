#include "shape.h"

Shape::Shape()
{

}

QPoint Shape::rotate_point(QPoint o, QPoint p, int d)
{
    QPoint result;
    result.setX((p.x()-o.x())*cos((double)d*3.14/180)-(p.y()-o.y())*sin((double)d*3.14/180)+o.x());
    result.setY((p.x()-o.x())*sin((double)d*3.14/180)+(p.y()-o.y())*cos((double)d*3.14/180)+o.y());
    return result;
}

