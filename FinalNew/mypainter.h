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
#define WIDTH 1600
#define HEIGHT 900

enum modeCode { code_line, code_circle, code_ellipse, code_rect,code_polygon};

class MyPainter:public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);

public slots:
        void setCurrentMode(modeCode s)
        {
            curShapecontorl = s;
        }

private:
    QPixmap *pix;
    int curShapecontorl;
    std::vector<ShapeControl*>shapecontrol;
    std::vector<Shape*>all_shape;

protected:
   void paintEvent(QPaintEvent* e);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

};
#endif // MYPAINTER_H
