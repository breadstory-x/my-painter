#ifndef POLYGONCONTROL_H
#define POLYGONCONTROL_H
#include"shapecontrol.h"
#include"polygon.h"

class PolygonControl:public ShapeControl
{
public:
    PolygonControl();
    PolygonControl(std::vector<Shape*> *all_shape);

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e);

    void scale(double x);
    bool isEmpty();
    void clear_cur();
    bool is_cur_null();
private:
    Polygon* curpolygon;
    int press_node;
    bool polygon_finish;
    std::vector<Polygon*>all_polygon;
};

#endif // POLYGONCONTROL_H
