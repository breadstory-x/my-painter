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

private:
    Polygon* curpolygon;
    int press_node;
    bool polygon_finish;

};

#endif // POLYGONCONTROL_H
