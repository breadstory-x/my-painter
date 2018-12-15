#ifndef CURVCONTROL_H
#define CURVCONTROL_H
#include"shapecontrol.h"
#include"curve.h"
class CurveControl:public ShapeControl
{
public:
    CurveControl();
    CurveControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e);
    void onMouseReleaseEvent(QMouseEvent *e);

    void scale(double x);
    bool isEmpty();
    void clear_cur();
    bool is_cur_null();
private:
    Curve* curcurve;
    int press_node;
    bool curve_finish;
    std::vector<Curve*>all_curve;
};

#endif // CURVCONTROL_H
