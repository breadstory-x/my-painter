#include "vrect.h"

Vrect::Vrect()
{

}

void Vrect::paint(QPainter &painter)
{
    int startx = start.x()<end.x()?start.x():end.x();
    int starty = start.y()<end.y()?start.y():end.y();
    int endx = start.x()>end.x()?start.x():end.x();
    int endy = start.y()>end.y()?start.y():end.y();
    int num = 0;
    bool isVirtual = 0;
    for(int i = startx;i<=endx;i++)
    {
        if(num == 5)
        {
            isVirtual = !isVirtual;
            num = 0;
        }
        if(!isVirtual)
        {
            painter.drawPoint(i,start.y());
            painter.drawPoint(i,end.y());
        }
        num++;
    }

    for(int i = starty;i<=endy;i++)
    {
        if(num == 5)
        {
            isVirtual = !isVirtual;
            num = 0;
        }
        if(!isVirtual)
        {
            painter.drawPoint(start.x(),i);
            painter.drawPoint(end.x(), i);
        }
        num++;
    }
}

void Vrect::rotate_paint(QPainter &painter, int d)
{

}
