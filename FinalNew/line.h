#ifndef LINE_H
#define LINE_H
#include"shape.h"


class Line : public Shape
{
public:
    Line();
    Line(QPoint start, QPoint end);
    void paint(QPainter *painter);
    void mark_paint(QPainter *painter);
    //void clear();

    void translate(int x, int y);


    void setOtherPoint();//设置中点
    void setStart(QPoint start){this->start = start;}
    void setEnd(QPoint end){this->end = end;}
    QPoint getStart(){return start;}
    QPoint getEnd(){return end;}
    QPoint getCenter(){return center;}

private:
    QPoint start;
    QPoint end;

    QPoint center;
};

#endif // LINE_H
