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
private:
    std::vector<QPoint>poly_point;
    int i;
};

#endif // POLYGON_H
