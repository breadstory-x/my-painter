#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include"shape.h"
#include"line.h"
#include"circle.h"

enum shapeCode { code_line, code_circle };

class MyPainter : public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);

public slots:
        void setCurrentShape(shapeCode s)
        {
            shapecode = s;
        }

private://双缓冲
    QPixmap *pix;
    QPixmap *temppix;
    bool isDrawing;

protected:
   void paintEvent(QPaintEvent* e);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

private:
   Shape *shape;
   int shapecode;

};

#endif // MYPAINTER_H
