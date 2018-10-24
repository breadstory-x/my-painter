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
    virtual void paint(QPixmap *pix){}

protected:
        QPoint start;
        QPoint end;
};

#endif // SHAPE_H
