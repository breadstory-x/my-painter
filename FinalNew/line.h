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
    void setAngle(int angle){this->angle = angle;}
    QPoint getStart(){return start;}
    QPoint getEnd(){return end;}
    QPoint getCenter(){return center;}
    QPoint getRPoint(){return rotate_point;}
    int getAngle(){return angle;}


private:
    QPoint start;
    QPoint end;

    QPoint center;
    QPoint rotate_point;
    int angle;
};

#endif // LINE_H
