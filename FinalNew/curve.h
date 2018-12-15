#ifndef CURVE_H
#define CURVE_H
#include"shape.h"
#include<vector>
#include"line.h"

class Curve : public Shape
{
public:
    Curve();
    void paint(QPainter *painter);
    void mark_paint(QPainter *painter);
    //void clear();

    void translate(int x, int y);
    void scale(double s);

    std::vector<QPoint> &getCurve_point(){return curve_point;}
    void setFinish(bool x){finish = x;}
    bool getFinish(){return finish;}

    //void paint_line(QPainter *painter, int i, int j);
    void setOtherPoint();
    void setAngle(int angle){this->angle = angle;}
    QPoint getCenter(){return center;}
    QPoint getRPoint(){return rotate_point;}
    int getAngle(){return angle;}

private:
    std::vector<QPoint>curve_point;
    bool finish;
    //QPoint start_one;
    //QPoint start_two;
    //QPoint start_three;
    //QPoint start_four;
    QPoint center;
    QPoint rotate_point;
    int angle;
};

#endif // CURVE_H
