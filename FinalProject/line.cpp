#include "line.h"

Line::Line()
{

}


int prePrint_line(QPoint startPos, QPoint endPos)
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

void Line::paint(QPainter &painter)
{
    QPoint newstart = start, newend = end;
    if(end.x() < newstart.x())
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

    switch(prePrint_line(newstart, newend))
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


/*中点画线算法
    int a = newstart.y() - newend.y();
    int b = newend.x() - newstart.x();

    int d = 2*a + b;
    int delta1 = 2 * a ;
    int delta2 = 2 *( a + b);

    int x = newstart.x();
    int y = newstart.y();
    point.setX(x);
    point.setY(y);
    painter.drawPoint(point);

    switch (prePrint(newstart, newend)) {
    case 1:
        while(x < newend.x())
        {
            if(d < 0)
            {
                x++;
                y++;
                d+= delta2;
            }
            else
            {
                x++;
                d+=delta1;
            }
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
        }
        break;
    case 2:
        d = 2*a-b;
        delta1 = 2*(a-b);
        delta2 = 2*a;
        while(x < newend.x())
        {
            if(d < 0)
            {
                x++;
                d+= delta2;
            }
            else
            {
                y--;
                x++;
                d+=delta1;
            }
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
        }
        break;
    case 3:
        d = a+2*b;
        delta1 = 2*(a+b);
        delta2 = 2*b;
        while(y < newend.y())
        {
            if(d < 0)
            {
                y++;
                d+= delta2;
            }
            else
            {
                y++;
                x++;
                d+=delta1;
            }
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
        }
        break;
    case 4:
        d = a-2*b;
        delta1 = -2*b;
        delta2 = 2*(a-b);
        while(y > newend.y())
        {
            if(d < 0)
            {
                x++;
                y--;
                d+= delta2;
            }
            else
            {
                y--;
                d+=delta1;
            }
            point.setX(x);
            point.setY(y);
            painter.drawPoint(point);
        }
        break;
    default:
        break;
    }
*/
}
