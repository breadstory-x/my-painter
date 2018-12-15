#include "mypainter.h"

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
    pix=new QPixmap(WIDTH,HEIGHT);
    pix->fill(Qt::white);

    curShapecontorl = 0;
    press = 0;
    color = Qt::black;
    //origin_sw = new SelectWindow();
    shapecontrol.push_back(new LineControl(&all_shape));
    shapecontrol.push_back(new CircleControl(&all_shape));
    shapecontrol.push_back(new EllipseControl(&all_shape));
    shapecontrol.push_back(new RectControl(&all_shape));
    shapecontrol.push_back(new PolygonControl(&all_shape));
    shapecontrol.push_back(new CurveControl(&all_shape));

    setMaximumSize(1600,900);
    sw = new SWcontrol();
    setMouseTracking(true);
}

void MyPainter::clean()
{
    pix=new QPixmap(WIDTH,HEIGHT);
    pix->fill(Qt::white);

    curShapecontorl = 0;
    press = 0;
    color = Qt::black;
    //origin_sw = new SelectWindow();
    //shapecontrol.clear();
    shapecontrol[0] = new LineControl(&all_shape);
    shapecontrol[1] = new CircleControl(&all_shape);
    shapecontrol[2] = new EllipseControl(&all_shape);
    shapecontrol[3] = new RectControl(&all_shape);
    shapecontrol[4] = new PolygonControl(&all_shape);
    shapecontrol[5] = new CurveControl(&all_shape);
    all_shape.clear();
    sw = new SWcontrol();
    setMouseTracking(true);
    update();
}
void MyPainter::scale(double x)
{
    if(curShapecontorl < 6)
        if(shapecontrol[curShapecontorl]->isEmpty() || shapecontrol[curShapecontorl]->is_cur_null())
            QMessageBox::information(NULL,u8"error!",u8"请先画图形!");
        else
            shapecontrol[curShapecontorl]->scale(x);
    update();
}

void MyPainter::MyFill(QPoint x)
{
    for(int i = 0;i < 6; i++)
        shapecontrol[i]->clear_cur();
    QPainter toPixmap(pix);
    QPen pen;
    pen.setWidth(3);
    toPixmap.setPen(pen);
    for(int i = 0;i<all_shape.size();i++)
        all_shape[i]->paint(&toPixmap);
    QImage image = pix->toImage();
    QColor cur_color= image.pixelColor(x);
    if(cur_color == color)
        return;
    QStack<QPoint> s;
    s.push(x);
    while(!s.isEmpty())
     {
        //出栈，给当前扫描线上色
         QPoint newpoint = s.pop();
         image.setPixel(newpoint,color.rgb());
         int xleft = newpoint.rx()-1, xright = newpoint.rx()+1;
         int newy = newpoint.ry();
         while(xleft>=0 && image.pixelColor(xleft,newy) == cur_color)
         {
             image.setPixel(QPoint(xleft, newy),color.rgb());
             xleft--;
         }
         while(xright<WIDTH && image.pixelColor(xright,newy) == cur_color)
         {
             image.setPixel(QPoint(xright, newy),color.rgb());
             xright++;
         }
         //寻找当前扫描线上下行的seed点，并入栈
         int i;
         int flag = 0;
         if(newy + 1 < HEIGHT - 1)
         {
             for(i = xright-1;i>=xleft+1;i--)
             {
                 if(image.pixelColor(i,newy+1) == cur_color)
                     if(flag == 0)
                     {
                         flag = 1;
                         s.push(QPoint(i,newy+1));
                     }
                 else
                     flag = 0;
             }
         }
         flag = 0;
         if(newy-1>=0)
         {
             for(i = xright-1;i>=xleft+1;i--)
             {
                 if(image.pixelColor(i,newy-1) == cur_color)
                     if(flag == 0)
                     {
                         flag = 1;
                         s.push(QPoint(i,newy-1));
                     }
                 else
                     flag = 0;
             }
         }
     }
     pix = new QPixmap(QPixmap::fromImage(image));
     this->update();
}

void MyPainter::doCutPicture()
{
    if(shapecontrol[code_line]->isEmpty())
        QMessageBox::information(NULL,  u8"Error!", u8"请先画直线，再进行裁剪！");
    else if(sw->isNull())
        QMessageBox::information(NULL,  u8"Error!", u8"请指定裁剪范围！");
    else
    {
        shapecontrol[code_line]->cut(sw->getSW());
        update();
    }
}

void MyPainter::SaveFile(QString s)
{
    QPainter toPixmap(pix);
    QPen pen;
    pen.setWidth(3);
    toPixmap.setPen(pen);
    for(int i = 0;i<all_shape.size();i++)
        all_shape[i]->paint(&toPixmap);
    QImage image = pix->toImage();
    //toPixmap.save();
    image.save(s);
    QMessageBox::information(NULL,  u8"保存成功！", u8"保存成功！");

}

void MyPainter::mousePressEvent(QMouseEvent *e)
{
    press = 1;
    if(curShapecontorl < 6)
        shapecontrol[curShapecontorl]->onMousePressEvent(e);
    else if(curShapecontorl == code_fill)
        MyFill(e->pos());
    else if(curShapecontorl == code_select)
        sw->onMousePressEvent(e);
}

void MyPainter::mouseMoveEvent(QMouseEvent *e)
{
    if(press)
    {
        if(curShapecontorl < 6)
            shapecontrol[curShapecontorl]->onMouseMoveEvent(e);
        else if(curShapecontorl == code_select)
            sw->onMouseMoveEvent(e);
    }
    else
    {
        if(curShapecontorl<shapecontrol.size() && curShapecontorl<6)
        {
            if(shapecontrol[curShapecontorl]->onMousePassiveMoveEvent(e)== 1)
                setCursor(Qt::SizeAllCursor);
            else if(shapecontrol[curShapecontorl]->onMousePassiveMoveEvent(e) == 0)
                setCursor(Qt::ArrowCursor);
        }
        else if(curShapecontorl == code_select)
        {
            if(sw->onMousePassiveMoveEvent(e) == 1)
                setCursor(Qt::SizeAllCursor);
            else if(sw->onMousePassiveMoveEvent(e) == 0)
                setCursor(Qt::ArrowCursor);
        }
    }

    update();
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    if(curShapecontorl == code_curve)
        shapecontrol[curShapecontorl]->onMouseReleaseEvent(e);
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
    if(all_shape.size()>0 && curShapecontorl < 6)
        all_shape[all_shape.size()-1]->mark_paint(&painter);
    if(curShapecontorl == code_select)
    {
        pen.setColor(Qt::red);
        pen.setWidth(1);
        painter.setPen(pen);
        sw->paint(&painter);
    }

}
