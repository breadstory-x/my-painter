#include "ellipse.h"
#include<cmath>
Ellipse::Ellipse()
{

}

void Ellipse::paint(QPainter &painter)
{
   //painter.drawEllipse(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());
    double rx = abs(start.x()-end.x())/2;
    double ry = abs(start.y()-end.y())/2;
    double heartx = rx+(start.x()<end.x()?start.x():end.x());
    double hearty = ry+(start.y()<end.y()?start.y():end.y());
    //double heartx = (start.x()+end.x())/2;
    //double hearty = (start.y()+end.y())/2;
    //double rx = heartx - (start.x()<end.x()?start.x():end.x());
    //double ry = hearty - (start.y()<end.y()?start.y():end.y());


    double x = 0;
    double y = ry;
    double p = ry*ry-rx*rx*ry+rx*rx*0.25;

    QPoint point;
    point.setX(x+heartx);
    point.setY(y+hearty);
    painter.drawPoint(point);
    point.setX(-x+heartx);
    point.setY(y+hearty);
    painter.drawPoint(point);
    point.setX(-x+heartx);
    point.setY(-y+hearty);
    painter.drawPoint(point);
    point.setX(x+heartx);
    point.setY(-y+hearty);
    painter.drawPoint(point);

    for(;2*ry*ry*x<2*rx*rx*y;x++)
    {
        if(p < 0)
        {
            p += ry*ry*(2*x+3);
        }
        else
        {
            p += 2*ry*ry*(x+3)-2*rx*rx*(y-1);
            y--;
        }
        point.setX(x+heartx);
        point.setY(y+hearty);
        painter.drawPoint(point);
        point.setX(-x+heartx);
        point.setY(y+hearty);
        painter.drawPoint(point);
        point.setX(-x+heartx);
        point.setY(-y+hearty);
        painter.drawPoint(point);
        point.setX(x+heartx);
        point.setY(-y+hearty);
        painter.drawPoint(point);
    }
    //p = ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
    //p = ry*(x+0.5)*2+(rx*(y-1))*2-(rx*ry)*2;
    for(;y>=0;y--)
    {
        if(p > 0)
        {
            p += rx*rx*(3-2*y);
        }
        else
        {
            p += 2*ry*ry*(x+1)+rx*rx*(3-2*y);
            x++;
        }
        point.setX(x+heartx);
        point.setY(y+hearty);
        painter.drawPoint(point);
        point.setX(-x+heartx);
        point.setY(y+hearty);
        painter.drawPoint(point);
        point.setX(-x+heartx);
        point.setY(-y+hearty);
        painter.drawPoint(point);
        point.setX(x+heartx);
        point.setY(-y+hearty);
        painter.drawPoint(point);
    }

}

void Ellipse::rotate_paint(QPainter &painter, int d)
{

}
