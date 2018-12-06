#ifndef SWCONTROL_H
#define SWCONTROL_H
#include"selectwindow.h"
#include<QMouseEvent>
#include<QPainter>
enum swPressNode{ELSE,START,END};
class SWcontrol
{
public:
    SWcontrol();

    void onMousePressEvent(QMouseEvent *event);
    void onMouseMoveEvent(QMouseEvent *event); //鼠标按下时鼠标的移动
    int onMousePassiveMoveEvent(QMouseEvent *e);

    void paint(QPainter *painter);
    bool isNull(){return cursw == NULL?true:false;}
    SelectWindow* getSW(){return cursw;}

private:
    SelectWindow* cursw;
    int press_node;
};

#endif // SWCONTROL_H
