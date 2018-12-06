#ifndef SHAPE_H
#define SHAPE_H

#include<QPoint>
#include<QPainter>
#include<QPen>
#include<QBrush>
class Shape
{
public:
    Shape();

   virtual void paint(QPainter *painter)=0; //绘制图形本身
   virtual void mark_paint(QPainter *painter)=0; //绘制除draw以外的标记：标记点(+矩形框)
 //   virtual void clear()=0; //清除图形中的点并释放空间

    virtual void translate(int x, int y)=0; //平移
    //virtual void rotate(double angle)=0; //旋转
    virtual void scale(double s)=0; //缩放
    QPoint scale_point(QPoint o, QPoint p, double s);
    QPoint rotatePoint(QPoint o, QPoint p, int d);
protected:
    std::vector<Shape*> *all_shape;
};

#endif // SHAPE_H
