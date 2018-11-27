#ifndef POLYGON_H
#define POLYGON_H
#include"shape.h"
#include<vector>


class Polygon
{
public:
    Polygon();
    int geti();
    std::vector<QPoint>& getPoint();
    void paint(QPainter &painter, int i, int j);
    void addi(){i++;}
    void seti(int j){i=j;}
    void paint_all(QPainter &painter);
    QPoint rotate_point(QPoint o, QPoint p, int d);
    void rotate(Polygon *p, int d);
    void scale(Polygon *s, double x);
    QPoint scale_point(QPoint o, QPoint p, double s);

private:
    std::vector<QPoint>poly_point;
    int i;
};

#endif // POLYGON_H
