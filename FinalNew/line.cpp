#include "line.h"

Line::Line()
{
    angle = 0;
}

Line::Line(QPoint start, QPoint end)
{
    this->start = start;
    this->end = end;
    angle = 0;
}

int prePrint_line(QPoint startPos, QPoint endPos)
{
    int x0 = startPos.x();
    int y0 = startPos.y();
    int x1 = endPos.x();
    int y1 = endPos.y();
    double slope = (double)(y1 - y0) / (x1 - x0);

    if(slope >= 0 && slope <= 1)
        return 1;
    if(slope >= -1 && slope <= 0)
        return 2;
    if(slope > 1)
        return 3;
    if(slope < -1)
        return 4;
}

void Line::paint(QPainter *painter)
{
    painter->translate(center.x(),center.y());
    painter->rotate(angle);
    painter->translate(-center.x(),-center.y());

    QPoint newstart = start, newend = end;
    if(newend.x() < newstart.x())
    {
        QPoint temp = newstart;
        newstart = newend;
        newend = temp;
    }

    QPoint point;

    int x = newstart.x();
    int y = newstart.y();
    int dx = newend.x() - newstart.x();
    int dy = newend.y()-newstart.y();
    int p = 2*dy-dx;

    switch(prePrint_line(newstart, newend))
    {
    case 1:
        for(;x < newend.x();x++)
        {
            point.setX(x);
            point.setY(y);
            painter->drawPoint(point);
            if(p >= 0)
            {
                y++;
                p += 2*(dy-dx);
            }
            else
                p+= 2*dy;
        }
        break;
    case 2:
        p = 2*dy+dx;
        for(;x < newend.x();x++)
        {
            point.setX(x);
            point.setY(y);
            painter->drawPoint(point);
            if(p >= 0)
            {
                p += 2*(dy);
            }
            else
            {
                y--;
                p+= 2*(dy+dx);
            }
        }
        break;
    case 3:
        p = 2*dx -dy;
        for(;y < newend.y();y++)
        {
            point.setX(x);
            point.setY(y);
            painter->drawPoint(point);
            if(p >= 0)
            {
                x++;
                p += 2*(dx-dy);
            }
            else
            {
                p+= 2*(dx);
            }
        }
        break;
    case 4:
        p = -2*dx - dy;
        for(;y > newend.y();y--)
        {
            point.setX(x);
            point.setY(y);
            painter->drawPoint(point);
            if(p >= 0)
            {
                p -= 2*(dx);
            }
            else
            {
                x++;
                p -= 2*(dx+dy);
            }
        }
        break;

    }

    painter->translate(center.x(),center.y());
    painter->rotate(-angle);
    painter->translate(-center.x(),-center.y());
}

void Line::mark_paint(QPainter *painter)
{
    paint(painter);

    QPainter assist_painter(painter->device());//用于画辅助线和控制点的painter

    assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(angle);
    assist_painter.translate(-center.x(),-center.y());

    QPen pen;
    pen.setWidth(1);
    pen.setColor(Qt::blue);
    assist_painter.setPen(pen);
    assist_painter.setBrush(Qt::white);
    if(angle == 0)//没有旋转的时候可以编辑
    {
        assist_painter.drawEllipse(start.x()-5,start.y()-5,10,10);
        assist_painter.drawEllipse(end.x()-5,end.y()-5,10,10);
    }
    assist_painter.drawEllipse(center.x()-5,center.y()-5,10,10);
    assist_painter.drawEllipse(rotate_point.x()-5,rotate_point.y()-5,10,10);

    assist_painter.translate(center.x(),center.y());
    assist_painter.rotate(-angle);
    assist_painter.translate(-center.x(),-center.y());

}

void Line::setOtherPoint()
{
    center.setX((start.x()+end.x())/2);
    center.setY((start.y()+end.y())/2);

    double k = ((double)(start.y()-end.y()))/(start.x()-end.x());//当前直线斜率
    double k2 = -1/k;//带求直线斜率，即tanθ
    double x = atan(k2);//角度
    //double sinx = k2/sqrt(1+k2*k2);
    //double cosx = 1/sqrt(1+k2*k2);

    if(k>0)
    {
        rotate_point.setX(center.x()+40*cos(x));
        rotate_point.setY(center.y()+40*sin(x));
    }
    else
    {
        rotate_point.setX(center.x()-40*cos(x));
        rotate_point.setY(center.y()-40*sin(x));
    }
}

void Line::translate(int x, int y)
{
    start.rx() += x;
    start.ry() += y;
    end.rx()+=x;
    end.ry()+=y;
}

void Line::scale(double s)
{
    start = scale_point(center,start, s);
    end = scale_point(center,end, s);
    setOtherPoint();
}
