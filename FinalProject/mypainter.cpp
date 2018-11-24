#include "mypainter.h"
#include<QDebug>
#include<vector>
#include<QImage>
#include<QColor>
#include<QStack>
#include<QCursor>
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
     isEdit = false;
     isStart = false;
     LBDown = false;
     poly_finish = true;
     poly_edit_num = 0;

     shape = NULL;
     polygon = new Polygon;
     modecode = code_line;
     width = 3;
     color = Qt::black;

     setMouseTracking(true);
}


void MyPainter::mousePressEvent(QMouseEvent *e)
{
  //记录第一次点击的鼠标的起始坐标
    LBDown = true;
    if(shape != NULL)//判断是否为编辑模式
    {
        if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
        {
            if(   (shape->getStart().rx()-10<e->pos().rx() && e->pos().rx()<shape->getStart().rx()+10)
                &&(shape->getStart().ry()-10<e->pos().ry() && e->pos().ry()<shape->getStart().ry()+10))
            {
                isEdit = true;
                isStart = true;
            }
            else if(  (shape->getEnd().rx()-10<e->pos().rx() && e->pos().rx()<shape->getEnd().rx()+10)
                    &&(shape->getEnd().ry()-10<e->pos().ry() && e->pos().ry()<shape->getEnd().ry()+10))
             {
                isEdit = true;
                isStart = false;
            }
            if(isEdit == true)
            {
                //先将要编辑的图像清空
                QPainter painter(pix);
                QPen pen;
                pen.setWidth(width);
                pen.setColor(Qt::white);
                painter.setPen(pen);
                shape->paint(painter);
                this->update();
                isDrawing = true;
                return;
            }
        }
        else if(modecode == code_polygon)
        {
            for(int i = 0;i < polygon->getPoint().size();i++)
            {
                if((polygon->getPoint()[i].rx()-10<e->pos().rx() && e->pos().rx()<polygon->getPoint()[i].rx()+10)
                 &&(polygon->getPoint()[i].ry()-10<e->pos().ry() && e->pos().ry()<polygon->getPoint()[i].ry()+10))
                {
                    isEdit = true;
                    poly_edit_num = i;

                    QPainter painter(pix);
                    QPen pen;
                    pen.setWidth(width);
                    pen.setColor(Qt::white);
                    painter.setPen(pen);
                    polygon->paint(painter, poly_edit_num, (poly_edit_num-1+polygon->getPoint().size())%polygon->getPoint().size());
                    polygon->paint(painter, poly_edit_num, (poly_edit_num+1)%polygon->getPoint().size());
                    this->update();
                    isDrawing=true;
                    return;
                }
            }
        }
    }

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
    case code_rect:
        shape = new Rectangle;
        break;
    default:
        shape = new Line;
        break;
    }
    if(modecode == code_polygon)
        {
            if(poly_finish == true)
            {
                polygon->getPoint().clear();
                polygon->seti(0);
                poly_finish = false;
                //poly_edit_num = 0;
            }
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
                    poly_finish = true;
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
    else
    {
        shape->setStart(e->pos());
        isDrawing = true;
    }


}


//然后拖拉鼠标，寻找到一个新的结束点，然后绘画到图片
void MyPainter::mouseMoveEvent(QMouseEvent *e)
{
    if(LBDown)//如果鼠标被按下
    {
        if(isEdit)
        {
            if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
            {
                if(isStart)
                    shape->setStart(e->pos());
                else if(!isStart)
                    shape->setEnd(e->pos());
                this->update();
            }
            else if(modecode == code_polygon)
            {
                polygon->getPoint()[poly_edit_num] = e->pos();
                this->update();
            }
        }
        else
        {
            if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
            {
                shape->setEnd(e->pos());
                this->update();
            }
        }
    }
    if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
        if( shape != NULL &&
            (( (shape->getStart().rx()-10<e->pos().rx() && e->pos().rx()<shape->getStart().rx()+10)
            &&(shape->getStart().ry()-10<e->pos().ry() && e->pos().ry()<shape->getStart().ry()+10))
            ||
            ( (shape->getEnd().rx()-10<e->pos().rx() && e->pos().rx()<shape->getEnd().rx()+10)
            &&(shape->getEnd().ry()-10<e->pos().ry() && e->pos().ry()<shape->getEnd().ry()+10))))
            setCursor(Qt::SizeAllCursor);
        else
            setCursor(Qt::ArrowCursor);
    else if(modecode == code_polygon)
        for(int i = 0;i < polygon->getPoint().size();i++)
            if((polygon->getPoint()[i].rx()-10<e->pos().rx() && e->pos().rx()<polygon->getPoint()[i].rx()+10)
             &&(polygon->getPoint()[i].ry()-10<e->pos().ry() && e->pos().ry()<polygon->getPoint()[i].ry()+10))
            {
                setCursor(Qt::SizeAllCursor);
                break;
            }
            else
                setCursor(Qt::ArrowCursor);
    /*else
    {
        qDebug()<<e->pos();
    }*/

}

void MyPainter::mouseReleaseEvent(QMouseEvent *e)
{
    LBDown = false;
    if(isEdit)
    {
        if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
        {
            isDrawing = false;
            isEdit = false;
            if(isStart)
                shape->setStart(e->pos());
            else if(!isStart)
                shape->setEnd(e->pos());

            QPainter painterx(pix);
            QPen pen;
            pen.setWidth(width);
            pen.setColor(color);
            painterx.setPen(pen);
            shape->paint(painterx);
            this->update();
        }
        else if(modecode == code_polygon)
        {
            isDrawing = false;
            isEdit = false;
            polygon->getPoint()[poly_edit_num] = e->pos();
            QPainter painterx(pix);
            QPen pen;
            pen.setWidth(width);
            pen.setColor(color);
            painterx.setPen(pen);
            polygon->paint(painterx, poly_edit_num, (poly_edit_num-1+polygon->getPoint().size())%polygon->getPoint().size());
            polygon->paint(painterx, poly_edit_num, (poly_edit_num+1)%polygon->getPoint().size());
            this->update();
        }

    }
    else
    {
        if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
        {
            isDrawing = false;
            shape->setEnd(e->pos());

            QPainter painterx(pix);
            QPen pen;
            pen.setWidth(width);
            pen.setColor(color);
            painterx.setPen(pen);
            shape->paint(painterx);

            //painterx.drawRect(shape->getStart().x()-5,shape->getStart().y()-5,10,10);
            //painterx.drawRect(shape->getEnd().x()-5,shape->getEnd().y()-5,10,10);
            this->update();
        }
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
        if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
            shape->paint(painterx);
        else if(modecode == code_polygon)
        {
            polygon->paint(painterx, poly_edit_num, (poly_edit_num-1+polygon->getPoint().size())%polygon->getPoint().size());
            polygon->paint(painterx, poly_edit_num, (poly_edit_num+1)%polygon->getPoint().size());
        }

        painter.drawPixmap(QPoint(0, 0), *temppix);
    }
    else
    {
        painter.drawPixmap(QPoint(0, 0), *pix);
    }
}
