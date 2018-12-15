#include "curve.h"

Curve::Curve()
{
    finish = false;
    angle = 0;
}

void Curve::paint(QPainter *painter)
{
    if(finish)
    {
        painter->translate(center.x(),center.y());
        painter->rotate(angle);
        painter->translate(-center.x(),-center.y());
    }
    if(curve_point.size() >0 && curve_point.size()<=4 && !finish)//没完成之前只画辅助线段
    {
        for(int i = 1;i<curve_point.size();i++)
        {
            QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter
            QPen pen;
            pen.setWidth(1);
            pen.setColor(Qt::blue);
            pen.setStyle(Qt::DashLine);
            assist_painter.setPen(pen);

            assist_painter.drawLine(curve_point[i-1],curve_point[i]);
        }
    }
    else if(finish)
    {
        int cx = curve_point[0].x();
        int cy = curve_point[0].y();

        int x0 = curve_point[0].x();
        int y0 = curve_point[0].y();
        int x1 = curve_point[1].x();
        int y1 = curve_point[1].y();
        int x2 = curve_point[2].x();
        int y2 = curve_point[2].y();
        int x3 = curve_point[3].x();
        int y3 = curve_point[3].y();
        painter->drawPoint(cx,cy);
        for(double i = 0;i<=1.0;i+=0.001)
        {
            cx = x0*(1-i)*(1-i)*(1-i)+3*x1*i*(1-i)*(1-i)+3*x2*i*i*(1-i)+x3*i*i*i;
            cy = y0*(1-i)*(1-i)*(1-i)+3*y1*i*(1-i)*(1-i)+3*y2*i*i*(1-i)+y3*i*i*i;
            painter->drawPoint(cx,cy);
        }
    }
    if(finish)
    {
        painter->translate(center.x(),center.y());
        painter->rotate(-angle);
        painter->translate(-center.x(),-center.y());
    }
}

void Curve::mark_paint(QPainter *painter)
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

        assist_painter.drawLine(curve_point[0],curve_point[1]);
        assist_painter.drawLine(curve_point[1],curve_point[2]);
        assist_painter.drawLine(curve_point[2],curve_point[3]);
        //assist_painter.drawLine(curve_point[3],curve_point[0]);

        pen.setStyle(Qt::SolidLine);
        assist_painter.setPen(pen);
        if(angle == 0)
            for(int i =0;i<curve_point.size();i++)
                assist_painter.drawEllipse(curve_point[i].x()-5,curve_point[i].y()-5,10,10);

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

}

void Curve::translate(int x, int y)
{
    for(int i=0;i<curve_point.size();i++)
    {
        curve_point[i].ry()+=y;
        curve_point[i].rx()+=x;
    }
}

void Curve::scale(double s)
{
    for(int i = 0;i<curve_point.size();i++)
        curve_point[i] = scale_point(center, curve_point[i], s);
    setOtherPoint();
}

void Curve::setOtherPoint()
{
    int maxx = curve_point[0].x();
    int minx = curve_point[0].x();
    int maxy = curve_point[0].y();
    int miny = curve_point[0].y();
    for(int i = 1;i<curve_point.size();i++)
    {
        if(curve_point[i].x()>maxx)
            maxx = curve_point[i].x();
        else if(curve_point[i].x()<minx)
            minx = curve_point[i].x();

        if(curve_point[i].y() > maxy)
            maxy = curve_point[i].y();
        else if(curve_point[i].y() < miny)
            miny = curve_point[i].y();
    }
    /*start_one.setX(minx);
    start_one.setY(miny);
    start_two.setX(maxx);
    start_two.setY(miny);
    start_three.setX(minx);
    start_three.setY(maxy);
    start_four.setX(maxx);
    start_four.setY(maxy);*/

    center.setX((minx+maxx)/2);
    center.setY((miny+maxy)/2);
    rotate_point.setX(center.x());
    rotate_point.setY(miny-40);

}
