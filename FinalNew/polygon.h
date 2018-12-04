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

    std::vector<QPoint> &getPoly_point(){return poly_point;}
    void setFinish(bool x){finish = x;}
    bool getFinish(){return finish;}

    //void paint_line(QPainter *painter, int i, int j);
    void setOtherPoint();
    QPoint getCenter(){return center;}
private:
    std::vector<QPoint>poly_point;
    bool finish;
    QPoint start_one;
    QPoint start_two;
    QPoint start_three;
    QPoint start_four;
    QPoint center;
};

#endif // POLYGON_H
