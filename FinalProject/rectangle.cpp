#include "rectangle.h"

Rectangle::Rectangle()
{

}
void Rectangle::paint(QPainter &painter)
{
    for(int i = start.x();i<=end.x();i++)
    {
        painter.drawPoint(i,start.y());
        painter.drawPoint(i,end.y());
    }
    for(int i = start.y();i<=end.y();i++)
    {
        painter.drawPoint(start.x(),i);
        painter.drawPoint(end.x(), i);
    }
}
