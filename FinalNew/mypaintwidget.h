#ifndef MYPAINTWIDGET_H
#define MYPAINTWIDGET_H
#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>

#define WIDTH 1600
#define HEIGHT 900

class MyPaintWidget:public QWidget
{
    Q_OBJECT
public:
    explicit MyPainter(QWidget *parent = nullptr);

private:
    QPixmap *pix;


protected:
   void paintEvent(QPaintEvent* e);
   void mousePressEvent(QMouseEvent *event);
   void mouseMoveEvent(QMouseEvent *event);
   void mouseReleaseEvent(QMouseEvent *event);

};

#endif // MYPAINTWIDGET_H
