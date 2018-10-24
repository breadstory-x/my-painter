#include "circle.h"

Circle::Circle()
{

}

void Circle::paint(QPixmap *pix)
{
    QPainter painter(pix);
    painter.drawEllipse(start.x(),start.y(),end.x()-start.x(),end.y()-start.y());
}
