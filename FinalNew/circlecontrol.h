#ifndef CIRCLECONTROL_H
#define CIRCLECONTROL_H
#include"shapecontrol.h"
#include"circle.h"


class CircleControl:public ShapeControl
{
public:
    CircleControl();
    CircleControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e);

private:
    Circle* curcircle;
    int press_node;
};

#endif // CIRCLECONTROL_H
