#include "ellipse.h"

Ellipse::Ellipse()
{
    angle = 0;
}

void Ellipse::paint(QPainter *painter)
{
    //painter.drawEllipse(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());

    painter->translate(center.x(),center.y());
    painter->rotate(angle);
    painter->translate(-center.x(),-center.y());

     double rx = abs(start_one.x()-start_four.x())/2;//长半轴
     double ry = abs(start_one.y()-start_four.y())/2;//短半轴
     double heartx = rx+(start_one.x()<start_four.x()?start_one.x():start_four.x());//中心x坐标
     double hearty = ry+(start_one.y()<start_four.y()?start_one.y():start_four.y());//中心y坐标

     double x = 0;
     double y = ry;
     double p = ry*ry-rx*rx*ry+rx*rx*0.25;

     painter->drawPoint(x+heartx, y+hearty);
     painter->drawPoint(-x+heartx, y+hearty);
     painter->drawPoint(-x+heartx, -y+hearty);
     painter->drawPoint(x+heartx, -y+hearty);

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

         painter->drawPoint(x+heartx, y+hearty);
         painter->drawPoint(-x+heartx, y+hearty);
         painter->drawPoint(-x+heartx, -y+hearty);
         painter->drawPoint(x+heartx, -y+hearty);
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

         painter->drawPoint(x+heartx, y+hearty);
         painter->drawPoint(-x+heartx, y+hearty);
         painter->drawPoint(-x+heartx, -y+hearty);
         painter->drawPoint(x+heartx, -y+hearty);
     }

     painter->translate(center.x(),center.y());
     painter->rotate(-angle);
     painter->translate(-center.x(),-center.y());
}

void Ellipse::mark_paint(QPainter *painter)
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
    if(angle == 0)
    {
        assist_painter.drawEllipse(start_one.x()-5,start_one.y()-5,10,10);
        assist_painter.drawEllipse(start_two.x()-5,start_two.y()-5,10,10);
        assist_painter.drawEllipse(start_three.x()-5,start_three.y()-5,10,10);
        assist_painter.drawEllipse(start_four.x()-5,start_four.y()-5,10,10);
    }

    //旋转点为橙色实心
    pen.setColor(QColor(255,200,0));
    assist_painter.setBrush(QColor(255,200,0));
    assist_painter.setPen(pen);
    assist_painter.drawEllipse(rotate_point.x()-5,rotate_point.y()-5,10,10);

    //中心点为天蓝色实心
    pen.setColor(QColor(85,170,255));
    assist_painter.setBrush(QColor(85,170,255));
    assist_painter.setPen(pen);
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);

    assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(-angle);
    assist_painter.translate(-center.x(),-center.y());

}

void Ellipse::translate(int x, int y)
{
    start_one.rx() += x;
    start_one.ry() += y;
    start_four.rx()+=x;
    start_four.ry()+=y;
}

void Ellipse::scale(double s)
{
    start_one = scale_point(center,start_one, s);
    start_two = scale_point(center,start_two, s);
    start_three = scale_point(center,start_three, s);
    start_four = scale_point(center,start_four, s);
    setOtherPoint();
}

void Ellipse::setOtherPoint()
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
