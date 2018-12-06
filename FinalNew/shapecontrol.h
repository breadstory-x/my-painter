#ifndef SHAPCONTROL_H
#define SHAPCONTROL_H
#include<QPoint>
#include<vector>
#include<QMouseEvent>
#include"shape.h"
#include<math.h>
#include<QDebug>
#include"swcontrol.h"
#include<QMessageBox>

enum CirclePressNode{OTHER,START_ONE,START_TWO,START_THREE,START_FOUR,CENTER, ROTATE};//START_ONE为起始点，其他的按顺时针旋转

class ShapeControl
{
public:
    ShapeControl();
    /*virtual void draw_all()=0;*/
    virtual void onMousePressEvent(QMouseEvent *event)=0;
    virtual void onMouseMoveEvent(QMouseEvent *event)=0; //鼠标按下时鼠标的移动
    virtual int onMousePassiveMoveEvent(QMouseEvent *e)=0; //鼠标未被按下时鼠标的移动

    virtual void scale(double x)=0;
    virtual bool isEmpty()=0;
    virtual void cut(SelectWindow *sw){}
    virtual void clear_cur()=0;
    virtual bool is_cur_null()=0;
protected:
    std::vector<Shape*> *all_shape;

};

#endif // SHAPCONTROL_H
