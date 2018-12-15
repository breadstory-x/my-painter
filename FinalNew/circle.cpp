#include "circle.h"

Circle::Circle()
{
    angle = 0;
}

void Circle::paint(QPainter *painter)
{
    /*int r;
    if(!(start_one.x()<start_four.x()&&start_one.y()<start_four.y()))
        r = 0;
    else*/
    /*painter->translate(center.x(),center.y());
    painter->rotate(angle);
    painter->translate(-center.x(),-center.y());*/

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

    /*painter->translate(center.x(),center.y());
    painter->rotate(-angle);
    painter->translate(-center.x(),-center.y());*/
}

void Circle::mark_paint(QPainter *painter)
{
    paint(painter);

    QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter

    /*assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(angle);
    assist_painter.translate(-center.x(),-center.y());*/

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
    //assist_painter.drawEllipse(start_two.x()-5,start_two.y()-5,10,10);
    //assist_painter.drawEllipse(start_three.x()-5,start_three.y()-5,10,10);
    assist_painter.drawEllipse(start_four.x()-5,start_four.y()-5,10,10);

    //中心点为天蓝色实心
    pen.setColor(QColor(85,170,255));
    assist_painter.setBrush(QColor(85,170,255));
    assist_painter.setPen(pen);
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);
    //assist_painter.drawEllipse(rotate_point.x()-5,rotate_point.y()-5,10,10);

    /*assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(-angle);
    assist_painter.translate(-center.x(),-center.y());*/

}

void Circle::translate(int x, int y)
{
    start_one.rx() += x;
    start_one.ry() += y;
    start_four.rx()+=x;
    start_four.ry()+=y;
}

void Circle::scale(double s)
{
    start_one = scale_point(center,start_one, s);
    start_two = scale_point(center,start_two, s);
    start_three = scale_point(center,start_three, s);
    start_four = scale_point(center,start_four, s);
    setOtherPoint();
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

void Circle::setExactOne(QPoint old_one)
{
    int startx = start_four.x();
    int starty = start_four.y();
    int endx = old_one.x();
    int endy = old_one.y();
    int flag = 1;
    if(startx < endx || starty < endy)
        flag = 1;
    else if(startx >= endx || starty >= endy)
        flag = -1;

    if(abs(startx-endx) > abs(starty-endy))
    {
        start_one.setX(startx+flag*abs(starty-endy));
        start_one.setY(endy);
    }
    else if(abs(startx-endx) <= abs(starty-endy))
    {
        start_one.setX(endx);
        start_one.setY(starty+flag*abs(startx-endx));
    }
}

void Circle::setExactFour(QPoint old_four)
{
    int startx = start_one.x();
    int starty = start_one.y();
    int endx = old_four.x();
    int endy = old_four.y();
    int flag = 1;
    if(startx < endx || starty < endy)
        flag = 1;
    else if(startx >= endx || starty >= endy)
        flag = -1;

    if(abs(startx-endx) > abs(starty-endy))
    {
        start_four.setX(startx+flag*abs(starty-endy));
        start_four.setY(endy);
    }
    else if(abs(startx-endx) <= abs(starty-endy))
    {
        start_four.setX(endx);
        start_four.setY(starty+flag*abs(startx-endx));
    }
}
