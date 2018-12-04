#ifndef SHAPCONTROL_H
#define SHAPCONTROL_H
#include<QPoint>
#include<vector>
#include<QMouseEvent>
#include"shape.h"

enum CirclePressNode{OTHER,START_ONE,START_TWO,START_THREE,START_FOUR,CENTER};//START_ONE为起始点，其他的按顺时针旋转

class ShapeControl
{
public:
    ShapeControl();
    /*virtual void draw_all()=0;*/
    virtual void onMousePressEvent(QMouseEvent *event)=0;
    virtual void onMouseMoveEvent(QMouseEvent *event)=0; //鼠标按下时鼠标的移动
    //virtual void onMousePassiveMoveEvent(QMouseEvent *event)=0; //鼠标未被按下时鼠标的移动

protected:
    std::vector<Shape*> *all_shape;

};

#endif // SHAPCONTROL_H
