#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<vector>
#include"shape.h"
#include"shapecontrol.h"
#include"linecontrol.h"
#include"circlecontrol.h"
#include"ellipsecontrol.h"
#include"rectcontrol.h"
#include"polygoncontrol.h"
#include"swcontrol.h"
#include"selectwindow.h"
#include<QMessageBox>
#include<QStack>
#define WIDTH 1600
#define HEIGHT 900

enum modeCode { code_line, code_circle, code_ellipse, code_rect,code_polygon, code_curve, code_fill, code_select};

class MyPainter:public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);

public slots:
        void setCurrentMode(modeCode s){ curShapecontorl = s;}
        void setCurrentColor(QColor c){ color = c; }
        void scale(double x);
        void doCutPicture();
        void SaveFile(QString s);
private:
    QPixmap *pix;//画布
    int curShapecontorl;//当前模式
    int press;//鼠标是否被按下
    QColor color;//当前颜色
    SWcontrol *sw;//裁剪框
    //SelectWindow *origin_sw;
    std::vector<ShapeControl*>shapecontrol;//存放所有图形的control类
    std::vector<Shape*>all_shape;//存放所有已画完的图形

public:
   void paintEvent(QPaintEvent* e);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);
   void MyFill(QPoint x);

};
#endif // MYPAINTER_H
