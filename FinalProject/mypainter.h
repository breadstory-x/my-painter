#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<QColor>
#include"shape.h"
#include"line.h"
#include"circle.h"
#include"ellipse.h"
#include"polygon.h"

enum modeCode { code_line, code_circle, code_ellipse, code_polygon, code_fill};

class MyPainter : public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);

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

private:
    QPixmap *pix;//画布
    QPixmap *temppix;//临时画布
    bool isDrawing;//是否在绘图
    Shape *shape;//图形对象，用于调用派生类的绘图函数
    Polygon *polygon;//多边形对象
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
