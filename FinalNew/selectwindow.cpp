#include "selectwindow.h"

SelectWindow::SelectWindow()
{

}

void SelectWindow::paint(QPainter *painter)
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
            painter->drawPoint(i,start.y());
            painter->drawPoint(i,end.y());
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
            painter->drawPoint(start.x(),i);
            painter->drawPoint(end.x(), i);
        }
        num++;
    }

    QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    assist_painter.setPen(pen);
    assist_painter.setBrush(Qt::white);

    assist_painter.drawEllipse(start.x()-5,start.y()-5,10,10);
    assist_painter.drawEllipse(end.x()-5,end.y()-5,10,10);
}
