#ifndef LINECONTROL_H
#define LINECONTROL_H
#include"shapecontrol.h"
#include"line.h"

class LineControl:public ShapeControl
{
public:
    LineControl();
    LineControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e); //鼠标未被按下时鼠标的移动

    void scale(double x);
    bool isEmpty();
    void cut(SelectWindow *sw);
    void clear_cur();
    bool is_cur_null();
private:
    Line* curline;
    int press_node;
    std::vector<Line*>all_line;
};

#endif // LINECONTROL_H
