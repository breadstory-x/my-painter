#include "polygon.h"

Polygon::Polygon()
{
    finish = false;
    angle = 0;
}

int prePrint_poly(QPoint startPos, QPoint endPos)
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

void Polygon::paint_line(QPainter *painter, int i, int j)
{
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

    switch(prePrint_poly(newstart, newend))
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

void Polygon::paint(QPainter *painter)
{
    if(finish)
    {
        painter->translate(center.x(),center.y());
        painter->rotate(angle);
        painter->translate(-center.x(),-center.y());
    }
    for(int i = 1;i<poly_point.size();i++)
    {
        //Line newline(poly_point[i-1],poly_point[i]);
        //newline.paint(painter);
        paint_line(painter,i-1,i);
    }
    if(finish == true)
    {
        //Line newline(poly_point[0],poly_point[poly_point.size()-1]);
        //newline.paint(painter);
        paint_line(painter, 0, poly_point.size()-1);
    }
    if(finish)
    {
        painter->translate(center.x(),center.y());
        painter->rotate(-angle);
        painter->translate(-center.x(),-center.y());
    }
}
void Polygon::mark_paint(QPainter *painter)
{
    paint(painter);
    if(finish)
    {
        QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter

        assist_painter.translate(center.x(),center.y());
        assist_painter.rotate(angle);
        assist_painter.translate(-center.x(),-center.y());

        QPen pen;
        pen.setWidth(1);
        pen.setColor(Qt::blue);
        pen.setStyle(Qt::DashLine);
        assist_painter.setPen(pen);
        assist_painter.setBrush(Qt::white);

        assist_painter.drawLine(start_one,start_two);
        assist_painter.drawLine(start_two,start_four);
        assist_painter.drawLine(start_three,start_four);
        assist_painter.drawLine(start_one,start_three);

        pen.setStyle(Qt::SolidLine);
        assist_painter.setPen(pen);
        if(angle == 0)
            for(int i =0;i<poly_point.size();i++)
                assist_painter.drawEllipse(poly_point[i].x()-5,poly_point[i].y()-5,10,10);

        assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);
        assist_painter.drawEllipse(rotate_point.x()-5,rotate_point.y()-5,10,10);

        assist_painter.translate(center.x(),center.y());
        assist_painter.rotate(-angle);
        assist_painter.translate(-center.x(),-center.y());
    }


}

void Polygon::translate(int x, int y)
{
    for(int i=0;i<poly_point.size();i++)
    {
        poly_point[i].ry()+=y;
        poly_point[i].rx()+=x;
    }
}

void Polygon::scale(double s)
{
    for(int i = 0;i<poly_point.size();i++)
        poly_point[i] = scale_point(center, poly_point[i], s);
    setOtherPoint();
}

void Polygon::setOtherPoint()
{
    int maxx = poly_point[0].x();
    int minx = poly_point[0].x();
    int maxy = poly_point[0].y();
    int miny = poly_point[0].y();
    for(int i = 1;i<poly_point.size();i++)
    {
        if(poly_point[i].x()>maxx)
            maxx = poly_point[i].x();
        else if(poly_point[i].x()<minx)
            minx = poly_point[i].x();

        if(poly_point[i].y() > maxy)
            maxy = poly_point[i].y();
        else if(poly_point[i].y() < miny)
            miny = poly_point[i].y();
    }
    start_one.setX(minx);
    start_one.setY(miny);
    start_two.setX(maxx);
    start_two.setY(miny);
    start_three.setX(minx);
    start_three.setY(maxy);
    start_four.setX(maxx);
    start_four.setY(maxy);

    center.setX((start_one.x()+start_four.x())/2);
    center.setY((start_one.y()+start_four.y())/2);
    rotate_point.setX(center.x());
    rotate_point.setY(start_one.y()-40);

}
