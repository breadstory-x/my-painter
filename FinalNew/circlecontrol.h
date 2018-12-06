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

    void scale(double x);
    bool isEmpty();
    void clear_cur();
    bool is_cur_null();
private:
    Circle* curcircle;
    int press_node;
    std::vector<Circle*>all_circle;
};

#endif // CIRCLECONTROL_H
