#ifndef ELLIPSECONTROL_H
#define ELLIPSECONTROL_H
#include"shapecontrol.h"
#include"ellipse.h"

class EllipseControl:public ShapeControl
{
public:
    EllipseControl();
    EllipseControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动

private:
    Ellipse* curellipse;
    int press_node;
};

#endif // ELLIPSECONTROL_H
