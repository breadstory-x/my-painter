#include "swcontrol.h"

SWcontrol::SWcontrol()
{
    cursw = NULL;
    press_node = ELSE;
}


void SWcontrol::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(cursw != NULL
       &&(cursw->getStart().rx()-10<event->pos().rx() && event->pos().rx()<cursw->getStart().rx()+10)
       &&(cursw->getStart().ry()-10<event->pos().ry() && event->pos().ry()<cursw->getStart().ry()+10))
        press_node = START;
    else if(cursw != NULL
            &&(cursw->getEnd().rx()-10<event->pos().rx() && event->pos().rx()<cursw->getEnd().rx()+10)
            &&(cursw->getEnd().ry()-10<event->pos().ry() && event->pos().ry()<cursw->getEnd().ry()+10))
        press_node = END;
    else
    {
        press_node = ELSE;
        cursw = new SelectWindow();
        cursw->setStart(event->pos());
    }
}

void SWcontrol::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START)
        cursw->setStart(event->pos());
    else if(press_node == END || press_node == ELSE)
        cursw->setEnd(event->pos());
}

int SWcontrol::onMousePassiveMoveEvent(QMouseEvent *e)
{
    if( cursw != NULL &&
        (((cursw->getStart().rx()-10<e->pos().rx() && e->pos().rx()<cursw->getStart().rx()+10)
        &&(cursw->getStart().ry()-10<e->pos().ry() && e->pos().ry()<cursw->getStart().ry()+10))
        ||
        ( (cursw->getEnd().rx()-10<e->pos().rx() && e->pos().rx()<cursw->getEnd().rx()+10)
        &&(cursw->getEnd().ry()-10<e->pos().ry() && e->pos().ry()<cursw->getEnd().ry()+10))))
        return 1;
    else
        return 0;
}

void SWcontrol::paint(QPainter *painter)
{
    if(cursw != NULL)
        cursw->paint(painter);
}
