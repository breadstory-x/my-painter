#ifndef SHAPE_H
#define SHAPE_H
#include<QPainter>
#include<QPixmap>
#include<cmath>
class Shape
{
public:
    Shape();
    void setStart(QPoint s){ start = s; }
    void setEnd(QPoint e){ end = e; }
    QPoint getStart(){ return start; }
    QPoint getEnd(){ return end; }
    virtual void paint(QPainter &painter)=0;
    virtual void rotate(Shape *s, int d)=0;
    QPoint rotate_point(QPoint o, QPoint p, int d);
    void scale(Shape *s, double x);
    QPoint scale_point(QPoint o, QPoint p, double s);

protected:
        QPoint start;
        QPoint end;
};

#endif // SHAPE_H
