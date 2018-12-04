#include "circle.h"
#include<cmath>
Circle::Circle()
{

}

void Circle::paint(QPainter &painter)
{
    //painter.drawEllipse(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());
    int r = abs((start.y() - end.y())/2)>abs((start.x() - end.x())/2)?abs((start.y() - end.y())/2):abs((start.x() - end.x())/2);//半径
    int rx = r + (start.x()<end.x()?start.x():end.x());
    int ry = r + (start.y()<end.y()?start.y():end.y());
    //int rx = r + start.x();
    //int ry = r + start.y();

    int x = 0;
    int y = r;
    int d = 1-r;
    int deltax = 3;
    int deltay = 5 - 2*r;

    QPoint point;
    point.setX(x+rx);
    point.setY(y+ry);
    painter.drawPoint(point);

    for(; x<y; x++)
    {
        if(d <0)
        {
            d+=deltax;
            deltax+=2;
            deltay+=2;
        }
        else
        {
            d+=deltay;
            deltax+=2;
            deltay+=4;
            y--;
        }
        point.setX(x+rx);
        point.setY(y+ry);
        painter.drawPoint(point);
        point.setX(-x+rx);
        point.setY(y+ry);
        painter.drawPoint(point);
        point.setX(-x+rx);
        point.setY(-y+ry);
        painter.drawPoint(point);
        point.setX(x+rx);
        point.setY(-y+ry);
        painter.drawPoint(point);
        point.setX(y+rx);
        point.setY(x+ry);
        painter.drawPoint(point);
        point.setX(-y+rx);
        point.setY(x+ry);
        painter.drawPoint(point);
        point.setX(-y+rx);
        point.setY(-x+ry);
        painter.drawPoint(point);
        point.setX(y+rx);
        point.setY(-x+ry);
        painter.drawPoint(point);
    }

    //重置结束点，以便对称
    if((start.x()+2*r == end.x() || start.x()-2*r == end.x()) && end.y() > start.y())
        end.setY(start.y()+2*r);
    else if((start.x()+2*r == end.x() || start.x()-2*r == end.x())&& end.y() < start.y())
        end.setY(start.y()-2*r);
    else if((start.y()+2*r == end.y() || start.y()-2*r == end.y()) && end.x() > start.x())
        end.setX(start.x()+2*r);
    else if((start.y()+2*r == end.y() || start.y()-2*r == end.y()) && end.x() < start.x())
        end.setX(start.x()-2*r);

}


void Circle::rotate_paint(QPainter &painter)
{
    painter.translate(start.x(),start.y());
    painter.rotate(angle);
    painter.translate(-start.x(),-start.y());
    paint(painter);
    //画完了还原坐标系
    painter.translate(start.x(),start.y());
    painter.rotate(-angle);
    painter.translate(-start.x(),-start.y());
}
