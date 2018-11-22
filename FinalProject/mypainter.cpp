#include "mypainter.h"
#include<QDebug>
#include<vector>

MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
     setAutoFillBackground(true);    //自动设定背景颜色
     //setPalette(QPalette(Qt::white));      //设置调色板的颜色为白色
     pix=new QPixmap(1600,900);    //这个pixmap对象用来接受准备绘制到空间的内容
     pix->fill(Qt::white);     //填充这个图片的背景是白色
     temppix=new QPixmap(1600,900);
     //temppix->fill(Qt::yellow);
     setMinimumSize(640,480);     //设置绘图区域窗体的最小大小
     isDrawing = false;
     modecode = 0;
     width = 1;

     polygon = new Polygon;

}


void MyPainter::mousePressEvent(QMouseEvent *e)
{
  //记录第一次点击的鼠标的起始坐标
    switch (modecode) {
    case code_line:
        shape = new Line;
        break;
    case code_circle:
        shape = new Circle;
        break;
    case code_ellipse:
        shape = new Ellipse;
        break;
    default:
        shape = new Line;
        break;
    }
    if(modecode == code_polygon)
    {
        QPainter painter(pix);
        QPen pen;
        pen.setWidth(width);
        pen.setColor(color);
        painter.setPen(pen);
        if(e->button() == Qt::LeftButton)
        {
            //qDebug()<<polygon->getPoint().size();
            if(polygon->getPoint().size() == 0)
            {
                polygon->getPoint().push_back(e->pos());
                painter.drawPoint(e->pos());
                this->update();
            }
            else if(polygon->getPoint().size() != 0)
            {
                polygon->getPoint().push_back(e->pos());
                polygon->addi();
                polygon->paint(painter, polygon->geti()-1, polygon->geti());
                this->update();
            }
        }
        else if(e->button() == Qt::RightButton)
        {
            if(polygon->getPoint().size() != 0)
            {
                polygon->paint(painter, polygon->getPoint().size()-1, 0);
                this->update();
                polygon->getPoint().clear();
                polygon->seti(0);
            }
        }

    }
    else
    {
        shape->setStart(e->pos());
        isDrawing = true;
    }
}

//然后拖拉鼠标，寻找到一个新的结束点，然后绘画到图片
void MyPainter::mouseMoveEvent(QMouseEvent *e)
{
    if(modecode != code_polygon)
    {
        shape->setEnd(e->pos());
        this->update();
    }
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    if(modecode != code_polygon)
    {
        isDrawing = false;
        shape->setEnd(e->pos());

        QPainter painterx(pix);
        QPen pen;
        pen.setWidth(width);
        pen.setColor(color);
        painterx.setPen(pen);
        shape->paint(painterx);

        this->update();
    }
}

//在调用paintEven之前，Qt会清除掉相应空间的内容,上面的update会调用paintEvent事件
void MyPainter::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    if(isDrawing)
    {
        *temppix = *pix;

        QPainter painterx(temppix);
        QPen pen;
        pen.setWidth(width);
        pen.setColor(color);
        painterx.setPen(pen);
        shape->paint(painterx);

        painter.drawPixmap(QPoint(0, 0), *temppix);
    }
    else
    {
        painter.drawPixmap(QPoint(0, 0), *pix);
    }
}
