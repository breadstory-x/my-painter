#include "rectange.h"

Rectange::Rectange()
{
    angle = 0;
}

void Rectange::paint(QPainter *painter)
{
    painter->translate(center.x(),center.y());
    painter->rotate(angle);
    painter->translate(-center.x(),-center.y());

    int startx = start_one.x()<start_four.x()?start_one.x():start_four.x();
    int starty = start_one.y()<start_four.y()?start_one.y():start_four.y();
    int endx = start_one.x()>start_four.x()?start_one.x():start_four.x();
    int endy = start_one.y()>start_four.y()?start_one.y():start_four.y();
    for(int i = startx;i<=endx;i++)
    {
        painter->drawPoint(i,start_one.y());
        painter->drawPoint(i,start_four.y());
    }
    for(int i = starty;i<=endy;i++)
    {
        painter->drawPoint(start_one.x(),i);
        painter->drawPoint(start_four.x(), i);
    }
    painter->translate(center.x(),center.y());
    painter->rotate(-angle);
    painter->translate(-center.x(),-center.y());
}

void Rectange::mark_paint(QPainter *painter)
{
    paint(painter);

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
    assist_painter.drawEllipse(start_one.x()-5,start_one.y()-5,10,10);
    assist_painter.drawEllipse(start_two.x()-5,start_two.y()-5,10,10);
    assist_painter.drawEllipse(start_three.x()-5,start_three.y()-5,10,10);
    assist_painter.drawEllipse(start_four.x()-5,start_four.y()-5,10,10);
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);
    assist_painter.drawEllipse(rotate_point.x()-5,rotate_point.y()-5,10,10);

    assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(-angle);
    assist_painter.translate(-center.x(),-center.y());

}

void Rectange::translate(int x, int y)
{
    start_one.rx() += x;
    start_one.ry() += y;
    start_four.rx()+=x;
    start_four.ry()+=y;
}

void Rectange::setOtherPoint()
{
    center.setX((start_one.x()+start_four.x())/2);
    center.setY((start_one.y()+start_four.y())/2);
    rotate_point.setX(center.x());
    rotate_point.setY(start_one.y()-40);

    start_two.setX(start_four.x());
    start_two.setY(start_one.y());
    start_three.setX(start_one.x());
    start_three.setY(start_four.y());
}
