#include "line.h"

Line::Line()
{

}

Line::Line(QPoint start, QPoint end)
{
    this->start = start;
    this->end = end;
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

void Line::paint(QPainter *painter)
{
    QPoint newstart = start, newend = end;
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

    switch(prePrint_line(newstart, newend))
    {
    case 1:
        for(;x < newend.x();x++)
        {
            point.setX(x);
            point.setY(y);
            painter->drawPoint(point);
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
            painter->drawPoint(point);
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
            painter->drawPoint(point);
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
            painter->drawPoint(point);
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

void Line::mark_paint(QPainter *painter)
{
    paint(painter);

    QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter
    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    assist_painter.setPen(pen);
    assist_painter.setBrush(Qt::white);
    assist_painter.drawEllipse(start.x()-5,start.y()-5,10,10);
    assist_painter.drawEllipse(end.x()-5,end.y()-5,10,10);
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);

}

void Line::setOtherPoint()
{
    center.setX((start.x()+end.x())/2);
    center.setY((start.y()+end.y())/2);
}

void Line::translate(int x, int y)
{
    start.rx() += x;
    start.ry() += y;
    end.rx()+=x;
    end.ry()+=y;
}
