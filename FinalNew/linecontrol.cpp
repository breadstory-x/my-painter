#include "linecontrol.h"

LineControl::LineControl()
{
    curline = NULL;
    press_node = OTHER;
}

LineControl::LineControl(std::vector<Shape*> *all_shape)
{
    curline = NULL;
    this->all_shape = all_shape;
    press_node = OTHER;
}

void LineControl::onMousePressEvent(QMouseEvent *event)
{
    //判断点击处在直线开始点、结束点、其他位置
    if(curline != NULL
       &&(curline->getStart().rx()-10<event->pos().rx() && event->pos().rx()<curline->getStart().rx()+10)
       &&(curline->getStart().ry()-10<event->pos().ry() && event->pos().ry()<curline->getStart().ry()+10))
        press_node = START_ONE;
    else if(curline != NULL
            &&(curline->getEnd().rx()-10<event->pos().rx() && event->pos().rx()<curline->getEnd().rx()+10)
            &&(curline->getEnd().ry()-10<event->pos().ry() && event->pos().ry()<curline->getEnd().ry()+10))
        press_node = START_FOUR;
    else if(curline != NULL
            &&(curline->getCenter().rx()-10<event->pos().rx() && event->pos().rx()<curline->getCenter().rx()+10)
            &&(curline->getCenter().ry()-10<event->pos().ry() && event->pos().ry()<curline->getCenter().ry()+10))
        press_node = CENTER;
    else
    {
        press_node = OTHER;
        curline = new Line();
        all_shape->push_back(curline);
        curline->setStart(event->pos());
    }
}

void LineControl::onMouseMoveEvent(QMouseEvent *event)
{
    if(press_node == START_ONE)
        curline->setStart(event->pos());
    else if(press_node == START_FOUR || press_node == OTHER)
        curline->setEnd(event->pos());
    else if(press_node == CENTER)
        curline->translate(event->pos().x()-curline->getCenter().x(), event->pos().y()-curline->getCenter().y());
    curline->setOtherPoint();
}
