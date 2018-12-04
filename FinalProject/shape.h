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
    void setAngle(int a){ angle = a;}
    QPoint getStart(){ return start; }
    QPoint getEnd(){ return end; }
    int getAngle(){return angle;}

    virtual void paint(QPainter &painter)=0;
    virtual void rotate_paint(QPainter &painter)=0;
    void scale(Shape *s, double x);
    QPoint scale_point(QPoint o, QPoint p, double s);

protected:
        QPoint start;
        QPoint end;
        int angle;
};

#endif // SHAPE_H
