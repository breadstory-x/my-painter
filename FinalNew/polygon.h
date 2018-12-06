#ifndef POLYGON_H
#define POLYGON_H
#include"shape.h"
#include"line.h"
#include<vector>
class Polygon : public Shape
{
public:
    Polygon();
    void paint(QPainter *painter);
    void mark_paint(QPainter *painter);
    //void clear();

    void translate(int x, int y);
    void scale(double s);

    std::vector<QPoint> &getPoly_point(){return poly_point;}
    void setFinish(bool x){finish = x;}
    bool getFinish(){return finish;}

    void paint_line(QPainter *painter, int i, int j);
    void setOtherPoint();
    void setAngle(int angle){this->angle = angle;}
    QPoint getCenter(){return center;}
    QPoint getRPoint(){return rotate_point;}
    int getAngle(){return angle;}

private:
    std::vector<QPoint>poly_point;
    bool finish;
    QPoint start_one;
    QPoint start_two;
    QPoint start_three;
    QPoint start_four;
    QPoint center;
    QPoint rotate_point;
    int angle;
};

#endif // POLYGON_H
