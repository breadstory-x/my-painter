#include "mypainter.h"
#include<QDebug>
#include<vector>
#include<QImage>
#include<QColor>
#include<QStack>
#define WIDTH 1600
#define HEIGHT 900
MyPainter::MyPainter(QWidget *parent) : QWidget(parent)
{
     setAutoFillBackground(true);    //自动设定背景颜色
     //setPalette(QPalette(Qt::white));      //设置调色板的颜色为白色
     pix=new QPixmap(WIDTH,HEIGHT);    //这个pixmap对象用来接受准备绘制到空间的内容
     pix->fill(Qt::white);     //填充这个图片的背景是白色
     temppix=new QPixmap(WIDTH,HEIGHT);
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
    else if(modecode == code_fill)
    {
        QImage image = pix->toImage();
        QColor cur_color= image.pixelColor(e->pos());
        if(cur_color == color)
            return;
        //qDebug()<<cur_color;
        QStack<QPoint> s;
        s.push(e->pos());
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
            if(newy + 1 < HEIGHT - 1)
            {
                for(i = xright-1;i>=xleft+1;i--)
                {
                    if(image.pixelColor(i,newy+1) == cur_color)
                        break;
                }
                if(i>=xleft+1&&i<=xright-1)
                    s.push(QPoint(i,newy+1));
            }
            if(newy-1>=0)
            {
                for(i = xright-1;i>=xleft+1;i--)
                {
                    if(image.pixelColor(i,newy-1) == cur_color)
                        break;
                }
                if(i>=xleft+1&&i<=xright-1)
                    s.push(QPoint(i,newy-1));
            }
        }
        pix = new QPixmap(QPixmap::fromImage(image));
        this->update();

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
    if(modecode == code_circle || modecode == code_ellipse || modecode == code_line)
    {
        shape->setEnd(e->pos());
        this->update();
    }
}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    if(modecode == code_circle || modecode == code_ellipse || modecode == code_line)
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
