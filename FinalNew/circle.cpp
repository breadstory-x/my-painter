#include "circle.h"

Circle::Circle()
{

}

void Circle::paint(QPainter *painter)
{
    /*int r;
    if(!(start_one.x()<start_four.x()&&start_one.y()<start_four.y()))
        r = 0;
    else*/
    int r = abs((start_one.y() - start_four.y())/2)>abs((start_one.x() - start_four.x())/2)?abs((start_one.y() - start_four.y())/2):abs((start_one.x() - start_four.x())/2);//半径
    int rx = r + (start_one.x()<start_four.x()?start_one.x():start_four.x());//原点离圆心的距离
    int ry = r + (start_one.y()<start_four.y()?start_one.y():start_four.y());//原点离圆心的距离

    int x = 0;
    int y = r;
    int d = 1-r;
    int deltax = 3;
    int deltay = 5 - 2*r;

    painter->drawPoint(x+rx,y+ry);

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
        painter->drawPoint(x+rx,y+ry);
        painter->drawPoint(-x+rx,y+ry);
        painter->drawPoint(-x+rx,-y+ry);
        painter->drawPoint(x+rx,-y+ry);
        painter->drawPoint(y+rx,x+ry);
        painter->drawPoint(-y+rx,x+ry);
        painter->drawPoint(-y+rx,-x+ry);
        painter->drawPoint(y+rx,-x+ry);
    }
}

void Circle::mark_paint(QPainter *painter)
{
    paint(painter);

    QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter
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
    assist_painter.drawEllipse(start_one.x()-5,start_one.y()-5,10,10);
    assist_painter.drawEllipse(start_two.x()-5,start_two.y()-5,10,10);
    assist_painter.drawEllipse(start_three.x()-5,start_three.y()-5,10,10);
    assist_painter.drawEllipse(start_four.x()-5,start_four.y()-5,10,10);
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);

}

void Circle::translate(int x, int y)
{
    start_one.rx() += x;
    start_one.ry() += y;
    start_four.rx()+=x;
    start_four.ry()+=y;
}

void Circle::setOtherPoint()
{
    center.setX((start_one.x()+start_four.x())/2);
    center.setY((start_one.y()+start_four.y())/2);

    start_two.setX(start_four.x());
    start_two.setY(start_one.y());
    start_three.setX(start_one.x());
    start_three.setY(start_four.y());
}
