#include "polygon.h"
#include<QDebug>

Polygon::Polygon()
{
    i = 0;
}
std::vector<QPoint>& Polygon::getPoint()
{
    return poly_point;
}

int Polygon::geti()
{
    return i;
}

int prePrint(QPoint startPos, QPoint endPos)
{
    int x0 = startPos.x();
    int y0 = startPos.y();
    int x1 = endPos.x();
    int y1 = endPos.y();
    double slope = (double)(y1 - y0) / (x1 - x0);

    if(slope >= 0 && slope <= 1)
        return 1;
    if(slope >= -1 && slope <= 0)
        return 2;
    if(slope > 1)
        return 3;
    if(slope < -1)
        return 4;
}

void Polygon::paint(QPainter &painter, int i, int j)
{
    //qDebug() << i;
    QPoint newstart = poly_point[i], newend = poly_point[j];
    if(newend.x() < newstart.x())
    {
        QPoint temp = newstart;
        newstart = newend;
        newend = temp;
    }

    QPoint point;

    int x = newstart.x();
    int y = newstart.y();
    int dx = newend.x() - newstart.x();
    int dy = newend.y()-newstart.y();
    int p = 2*dy-dx;

    switch(prePrint(newstart, newend))
    {
    case 1:
        for(;x < newend.x();x++)
        {
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
            if(p >= 0)
            {
                y++;
                p += 2*(dy-dx);
            }
            else
                p+= 2*dy;
        }
        break;
    case 2:
        p = 2*dy+dx;
        for(;x < newend.x();x++)
        {
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
            if(p >= 0)
            {
                p += 2*(dy);
            }
            else
            {
                y--;
                p+= 2*(dy+dx);
            }
        }
        break;
    case 3:
        p = 2*dx -dy;
        for(;y < newend.y();y++)
        {
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
            if(p >= 0)
            {
                x++;
                p += 2*(dx-dy);
            }
            else
            {
                p+= 2*(dx);
            }
        }
        break;
    case 4:
        p = -2*dx - dy;
        for(;y > newend.y();y--)
        {
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
            if(p >= 0)
            {
                p -= 2*(dx);
            }
            else
            {
                x++;
                p -= 2*(dx+dy);
            }
        }
        break;

    }
}
