#ifndef MYPAINTER_H
#define MYPAINTER_H

#include <QWidget>
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<QColor>
#include<QPoint>
#include<QMessageBox>
#include"shape.h"
#include"line.h"
#include"circle.h"
#include"ellipse.h"
#include"polygon.h"
#include"rectangle.h"

enum modeCode { code_line, code_rect, code_circle, code_ellipse, code_polygon, code_fill};

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
        void SaveFile(QString s)
        {
            //qDebug()<<s;
            QImage image = pix->toImage();
            image.save(s,"JPG");
            QMessageBox::about(NULL,  u8"保存成功！", u8"保存成功！");
        }
private:
    QPixmap *pix;//画布
    QPixmap *temppix;//临时画布
    bool isDrawing;//是否在绘图
    bool isEdit;//是否在编辑
    bool isStart;//是否编辑起始点
    bool LBDown;//鼠标是否按下
    bool poly_finish;//多边形是否画完，对应是否按下右键
    int poly_edit_num;
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
