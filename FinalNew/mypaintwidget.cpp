#include "mypaintwidget.h"

MyPaintWidget::MyPaintWidget()
{
    pix=new QPixmap(WIDTH,HEIGHT);
    pix->fill(Qt::white);
}
