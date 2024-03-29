﻿#include "rectangle.h"

Rectangle::Rectangle()
{

}
void Rectangle::paint(QPainter &painter)
{
    int startx = start.x()<end.x()?start.x():end.x();
    int starty = start.y()<end.y()?start.y():end.y();
    int endx = start.x()>end.x()?start.x():end.x();
    int endy = start.y()>end.y()?start.y():end.y();
    for(int i = startx;i<=endx;i++)
    {
        painter.drawPoint(i,start.y());
        painter.drawPoint(i,end.y());
    }
    for(int i = starty;i<=endy;i++)
    {
        painter.drawPoint(start.x(),i);
        painter.drawPoint(end.x(), i);
    }
}

void Rectangle::rotate_paint(QPainter &painter)
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

