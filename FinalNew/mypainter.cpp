#include "mypainter.h"

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
    pix=new QPixmap(WIDTH,HEIGHT);
    pix->fill(Qt::white);

    curShapecontorl = 0;
    press = 0;
    shapecontrol.push_back(new LineControl(&all_shape));
    shapecontrol.push_back(new CircleControl(&all_shape));
    shapecontrol.push_back(new EllipseControl(&all_shape));
    shapecontrol.push_back(new RectControl(&all_shape));
    shapecontrol.push_back(new PolygonControl(&all_shape));

    setMouseTracking(true);
}


void MyPainter::mousePressEvent(QMouseEvent *e)
{
    press = 1;
    shapecontrol[curShapecontorl]->onMousePressEvent(e);
}

void MyPainter::mouseMoveEvent(QMouseEvent *e)
{
    if(press)
        shapecontrol[curShapecontorl]->onMouseMoveEvent(e);
    else
        if(shapecontrol[curShapecontorl]->onMousePassiveMoveEvent(e)== 1)
            setCursor(Qt::SizeAllCursor);
        else if(shapecontrol[curShapecontorl]->onMousePassiveMoveEvent(e) == 0)
            setCursor(Qt::ArrowCursor);
    update();
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    press = 0;
    update();
}

void MyPainter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawPixmap(QPoint(0, 0), *pix);
    for(int i = 0;i<all_shape.size();i++)
        all_shape[i]->paint(&painter);
    if(all_shape.size()>0)
        all_shape[all_shape.size()-1]->mark_paint(&painter);

}
