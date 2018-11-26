#ifndef SHAPE_H
#define SHAPE_H
#include<QPainter>
#include<QPixmap>

class Shape
{
public:
    Shape();
    void setStart(QPoint s){ start = s; }
    void setEnd(QPoint e){ end = e; }
    QPoint getStart(){ return start; }
    QPoint getEnd(){ return end; }
    virtual void paint(QPainter &painter)=0;
    virtual void rotate_paint(QPainter &painter, int d)=0;
    QPoint rotate_point(QPoint o, QPoint p, int d);

protected:
        QPoint start;
        QPoint end;
};

#endif // SHAPE_H
