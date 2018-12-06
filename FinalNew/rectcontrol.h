#ifndef RECTCONTROL_H
#define RECTCONTROL_H
#include"shapecontrol.h"
#include"rectange.h"

class RectControl:public ShapeControl
{
public:
    RectControl();
    RectControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e);

    void scale(double x);
    bool isEmpty();
    void clear_cur();
    bool is_cur_null();
private:
    Rectange* currect;
    int press_node;
    std::vector<Rectange*>all_rectange;
};

#endif // RECTCONTROL_H
