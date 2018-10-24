#include "mypainter.h"
#include<QDebug>

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
     setAutoFillBackground(true);    //自动设定背景颜色
     //setPalette(QPalette(Qt::white));      //设置调色板的颜色为白色
     pix=new QPixmap(600,400);    //这个pixmap对象用来接受准备绘制到空间的内容
     pix->fill(Qt::white);     //填充这个图片的背景是白色
     temppix=new QPixmap(600,400);
     //temppix->fill(Qt::yellow);
     setMinimumSize(600,400);     //设置绘图区域窗体的最小大小
     isDrawing = false;
     shapecode = 0;

}


void MyPainter::mousePressEvent(QMouseEvent *e)
{
  //记录第一次点击的鼠标的起始坐标
    switch (shapecode) {
    case code_line:
        shape = new Line;
        break;
    case code_circle:
        shape = new Circle;
        break;
    default:
        shape = new Line;
        break;
    }
    shape->setStart(e->pos());
    isDrawing = true;
}

//然后拖拉鼠标，寻找到一个新的结束点，然后绘画到图片
void MyPainter::mouseMoveEvent(QMouseEvent *e)
{
    shape->setEnd(e->pos());
    this->update();
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    isDrawing = false;
    shape->setEnd(e->pos());
    shape->paint(pix);
    this->update();
}

//在调用paintEven之前，Qt会清除掉相应空间的内容,上面的update会调用paintEvent事件
void MyPainter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(isDrawing)
    {
        *temppix = *pix;
        shape->paint(temppix);
        painter.drawPixmap(QPoint(0, 0), *temppix);
    }
    else
    {
        painter.drawPixmap(QPoint(0, 0), *pix);
    }
}
