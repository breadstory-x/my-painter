#include "shape.h"

Shape::Shape()
{

}

QPoint Shape::rotate_point(QPoint o, QPoint p, int d)
{
    QPoint result;
    double angle = (double)d*3.1415926/180;
    result.setX((p.x()-o.x())*cos(angle)-(p.y()-o.y())*sin(angle)+o.x());
    result.setY((p.x()-o.x())*sin(angle)+(p.y()-o.y())*cos(angle)+o.y());
    return result;
}

QPoint Shape::scale_point(QPoint o, QPoint p, double s)
{
    QPoint result;
    result.setX((double)p.x()*s+(double)o.x()*(1.0-s));
    result.setY((double)p.y()*s+(double)o.y()*(1.0-s));
    return result;
}

void Shape::scale(Shape *s, double x)
{
    start = s->getStart();
    end = scale_point(start, s->getEnd(), x);
}

