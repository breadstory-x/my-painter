#ifndef ELLIPSE_H
#define ELLIPSE_H

#include"shape.h"

class Ellipse : public Shape
{
public:
    Ellipse();
    void paint(QPainter *painter);
    void mark_paint(QPainter *painter);
    //void clear();

    void translate(int x, int y);
    void scale(double s);

    void setOtherPoint();//设置中点、第二三控制点
    void setStart_one(QPoint start){this->start_one = start;}
    void setStart_two(QPoint start){this->start_two = start;}
    void setStart_three(QPoint start){this->start_three = start;}
    void setStart_four(QPoint end){this->start_four = end;}
    void setAngle(int angle){this->angle = angle;}
    QPoint getStart_one(){return start_one;}
    QPoint getStart_two(){return start_two;}
    QPoint getStart_three(){return start_three;}
    QPoint getStart_four(){return start_four;}
    QPoint getCenter(){return center;}
    QPoint getRPoint(){return rotate_point;}
    int getAngle(){return angle;}


private:
    QPoint start_one;
    QPoint start_two;
    QPoint start_three;
    QPoint start_four;
    QPoint center;
    QPoint rotate_point;
    int angle;
};

#endif // ELLIPSE_H
