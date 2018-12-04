#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<QColor>
#include<QPoint>
#include<QMessageBox>
#include<vector>
#include<QDebug>
#include"shape.h"
#include"line.h"
#include"circle.h"
#include"ellipse.h"
#include"polygon.h"
#include"rectangle.h"
#include"vrect.h"
#define WIDTH 1600
#define HEIGHT 900
enum modeCode { code_line, code_rect, code_circle, code_ellipse, code_polygon, code_fill, code_select, code_transform};

class MyPainter : public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);
    void paint_all_shape(QPainter &painter);

public slots:
        void setCurrentMode(modeCode s)
        {
            modecode = s;
        }
        void setCurrentWidth(int x)
        {
            width = x;
        }
        void setCurrentColor(QColor c)
        {
            color = c;
        }
        void SaveFile(QString s)
        {
            //qDebug()<<s;
            QImage image = pix->toImage();
            image.save(s,"JPG");
            QMessageBox::information(NULL,  u8"保存成功！", u8"保存成功！");
        }
        void NewFile()
        {
            setAutoFillBackground(true);    //自动设定背景颜色
            pix=new QPixmap(WIDTH,HEIGHT);    //这个pixmap对象用来接受准备绘制到空间的内容
            pix->fill(Qt::white);     //填充这个图片的背景是白色
            temppix=new QPixmap(WIDTH,HEIGHT);

            isDrawing = false;
            isEdit = false;
            isStart = false;
            LBDown = false;
            poly_finish = true;
            poly_edit_num = 0;

            shape = NULL;
            polygon = NULL;
            tran_shape = NULL;
            tran_polygon = NULL;
            //modecode = code_line;
            width = 3;
            color = Qt::black;
            line.clear();
            c_e_r.clear();
            poly.clear();
            this->update();
            setMouseTracking(true);
        }
        void doCutPicture()
        {
            Vrect *q=dynamic_cast<Vrect *>(shape);
            if (q == NULL)
                QMessageBox::information(NULL,  u8"Error!", u8"请指定裁剪范围！");
            else if(line.size() == 0)
                QMessageBox::information(NULL,  u8"Error!", u8"请先画直线，再进行裁剪！");
            else
            {
                std::vector<int> will_del;//存储将要被删除的直线编号
                QPainter painter(pix);
                QPen pen;
                for(int index = 0;index<line.size();index++)
                {
                    pen.setWidth(width);
                    pen.setColor(Qt::white);
                    painter.setPen(pen);
                    line[index]->paint(painter);
                    //this->update();

                    //TODO:直线裁剪算法,梁友栋
                    bool flag = false;
                    float u1 = 0, u2 = 1, r;
                    int p[4],q[4];
                    //判断裁剪框的范围
                    int xmin = shape->getStart().x()<shape->getEnd().x()?shape->getStart().x():shape->getEnd().x();
                    int xmax = shape->getStart().x()>shape->getEnd().x()?shape->getStart().x():shape->getEnd().x();
                    int ymin = shape->getStart().y()<shape->getEnd().y()?shape->getStart().y():shape->getEnd().y();
                    int ymax = shape->getStart().y()>shape->getEnd().y()?shape->getStart().y():shape->getEnd().y();

                    p[0] = line[index]->getStart().x()-line[index]->getEnd().x(); //-△x
                    p[1] = -p[0];                                         //△x
                    p[2] = line[index]->getStart().y()-line[index]->getEnd().y(); //-△y
                    p[3] = -p[2];                                         //△y

                    q[0] = line[index]->getStart().x() - xmin;  //x1-xmin
                    q[1] = xmax - line[index]->getStart().x();  //xmax-x1
                    q[2] = line[index]->getStart().y() - ymin;  //y1-ymin
                    q[3] = ymax - line[index]->getStart().y();  //ymax-y1

                    for(int i = 0; i < 4; i++)
                    {
                        r = (float)q[i] / (float)p[i];
                        if(p[i] < 0)
                        {
                            u1 = u1>r?u1:r;
                            if(u1 > u2)
                            {
                                flag = true;
                            }
                        }
                        if(p[i] > 0)
                        {
                            u2 = u2<r?u2:r;
                            if(u1 > u2)
                            {
                                flag = true;
                            }
                        }
                        if(p[i] == 0 && q[i] < 0)
                            flag = true;
                    }
                    if(flag)
                    {
                        will_del.push_back(index);
                        continue;
                    }
                    //将交点作为起止点赋给裁剪后的直线
                    QPoint tempstart(line[index]->getStart().x() - u1*(line[index]->getStart().x()-line[index]->getEnd().x()),line[index]->getStart().y() - u1*(line[index]->getStart().y()-line[index]->getEnd().y()));
                    QPoint tempend(line[index]->getStart().x() - u2*(line[index]->getStart().x()-line[index]->getEnd().x()),line[index]->getStart().y() - u2*(line[index]->getStart().y()-line[index]->getEnd().y()));
                    line[index]->setStart(tempstart);
                    line[index]->setEnd(tempend);

                    pen.setColor(color);
                    painter.setPen(pen);
                    line[index]->paint(painter);
                }
                //删除完全在裁剪框之外的线段
                for(int i = (int)will_del.size() - 1;i >= 0;i--)
                    for(int j = (int)line.size()-1;j >= 0 ;j--)
                        if(j == will_del[i])
                        {
                            for(int k = j;k<line.size()-1;k++)
                                line[k] = line[k+1];
                            line.pop_back();
                            break;
                        }
                //此处将所有图形重新画一遍
                pen.setColor(color);
                painter.setPen(pen);
                paint_all_shape(painter);
                this->update();
            }
        }
        void rotate(int r)
        {
            QPainter painter(pix);
            QPen pen;
            pen.setWidth(width);
            pen.setColor(Qt::white);
            painter.setPen(pen);
            if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
            {
                if(shape == NULL)
                {
                    QMessageBox::information(NULL,  u8"请先画图形！", u8"请先画图形！");
                    return;
                }
                if(tran_shape != NULL)
                {
                    tran_shape->rotate_paint(painter);
                    delete tran_shape;
                }
                else
                    shape->rotate_paint(painter);
                switch (modecode) {
                case code_line:
                    tran_shape = new Line;
                    break;
                case code_circle:
                    tran_shape = new Circle;
                    break;
                case code_ellipse:
                    tran_shape = new Ellipse;
                    break;
                case code_rect:
                    tran_shape = new Rectangle;
                    break;
                }
                tran_shape->setStart(shape->getStart());
                tran_shape->setEnd(shape->getEnd());
                tran_shape->setAngle(r);
                pen.setColor(color);
                painter.setPen(pen);

                tran_shape->rotate_paint(painter);

                //重画
                paint_all_shape(painter);
            }
            else if(modecode == code_polygon)
            {
                if(polygon == NULL)
                {
                    QMessageBox::information(NULL,  u8"请先画图形！", u8"请先画图形！");
                    return;
                }
                if(tran_polygon != NULL)
                {
                    tran_polygon->paint_all(painter);
                    delete tran_polygon;
                }
                else
                    polygon->paint_all(painter);
                tran_polygon = new Polygon;
                tran_polygon->rotate(polygon,r);
                pen.setColor(color);
                painter.setPen(pen);
                tran_polygon->paint_all(painter);

                //重画
                paint_all_shape(painter);
            }

            this->update();
        }
        void scale(qreal s)
        {
            QPainter painter(pix);
            QPen pen;
            pen.setWidth(width);
            pen.setColor(Qt::white);
            painter.setPen(pen);
            if(modecode == code_circle || modecode == code_ellipse || modecode == code_line || modecode == code_rect)
            {
                if(shape == NULL)
                {
                    QMessageBox::information(NULL,  u8"请先画图形！", u8"请先画图形！");
                    return;
                }
                if(tran_shape != NULL)
                {
                    tran_shape->rotate_paint(painter);
                    delete tran_shape;
                }
                else
                {
                    shape->rotate_paint(painter);
                }
                switch (modecode) {
                case code_line:
                    tran_shape = new Line;
                    break;
                case code_circle:
                    tran_shape = new Circle;
                    break;
                case code_ellipse:
                    tran_shape = new Ellipse;
                    break;
                case code_rect:
                    tran_shape = new Rectangle;
                    break;
                }
                tran_shape->scale(shape,s);
                pen.setColor(color);
                painter.setPen(pen);
                tran_shape->rotate_paint(painter);
                //重画
                paint_all_shape(painter);
            }
            else if(modecode == code_polygon)
            {
                if(polygon == NULL)
                {
                    QMessageBox::information(NULL,  u8"请先画图形！", u8"请先画图形！");
                    return;
                }
                if(tran_polygon != NULL)
                {
                    tran_polygon->paint_all(painter);
                    delete tran_polygon;
                }
                else
                    polygon->paint_all(painter);
                tran_polygon = new Polygon;
                tran_polygon->scale(polygon,s);
                pen.setColor(color);
                painter.setPen(pen);
                tran_polygon->paint_all(painter);

                //重画
                paint_all_shape(painter);
            }
            this->update();
        }
private:
    QPixmap *pix;//画布
    QPixmap *temppix;//临时画布
    bool isDrawing;//是否在绘图
    bool isEdit;//是否在编辑
    bool isStart;//是否编辑起始点
    bool LBDown;//鼠标是否按下
    bool poly_finish;//多边形是否画完，对应是否按下右键
    int poly_edit_num;//当前编辑的是多边形的第几个点
    Shape *shape;//图形对象，用于调用派生类的绘图函数
    Polygon *polygon;//多边形对象
    Shape *tran_shape;//变换后的临时对象
    Polygon *tran_polygon;//变换后的临时多边形对象
    std::vector<Shape*>line;//已画完的直线，用于裁剪和变换
    std::vector<Shape*>c_e_r;//已画完的圆、椭圆、矩形，用于变换
    std::vector<Polygon*>poly;//已画完的多边形，用于变换
    int modecode;//当前选择的形状
    int width;//当前选择的画笔宽度
    QColor color;//当前选择的颜色

protected:
   void paintEvent(QPaintEvent* e);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYPAINTER_H
